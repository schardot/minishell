#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/redirection.h"

static volatile sig_atomic_t g_signal_received = 0;

int create_heredoc_temp_file(char **filename)
{
	int fd;
	*filename = malloc(strlen(".heredoc.tmp") + 1);
	if (!*filename)
		return -1;
	strcpy(*filename, ".heredoc.tmp");
	fd = open(*filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		free(*filename);
		return -1;
	}
	close(fd);
	return 0;
}

void heredoc_sigint_handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	exit(1);
}

int	write_heredoc_input(int fd, char *delimiter)
{
	char	*buf;

	while (1)
	{
		buf = readline("> ");
		if (!buf)
		{
			if (errno == EINTR)
				return -1;
			break;
		}
		if (strcmp(buf, delimiter) == 0)
		{
			free(buf);
			break;
		}
		if (write(fd, buf, strlen(buf)) < 0 || write(fd, "\n", 1) < 0)
		{
			perror("write");
			free(buf);
			return -1;
		}
		free(buf);
	}
	return 0;
}
int handle_heredoc_child(char *delimiter, char *filename)
{
	int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		return -1;
	}
	struct sigaction sa;
	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	int result = write_heredoc_input(fd, delimiter);
	close(fd);
	return result;
}
// Function to wait for the heredoc process to complete and check for errors
int wait_for_heredoc_process(pid_t pid, char *filename)
{
	int status;
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		unlink(filename);
		return -1;
	}
	else if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		unlink(filename);
		return -1;
	}
	return 0;
}

int	redirect_heredoc_input(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return -1;
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return -1;
	}
	close(fd);
	return 0;
}

int	handle_HEREDOC_redirection(t_scmd *node)
{
	char	*delimiter;
	char	*filename;
	pid_t	pid;

	delimiter = node->R_HEREDOC_delimiter;
	filename = NULL;

	if (create_heredoc_temp_file(&filename) < 0)
		return -1;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free(filename);
		return -1;
	}
	else if (pid == 0)
	{
		if (handle_heredoc_child(delimiter, filename) < 0)
			exit(1);
		exit(0);
	}
	struct sigaction sa;
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	int result = wait_for_heredoc_process(pid, filename);
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	if (result < 0)
	{
		free(filename);
		return -1;
	}
	if (redirect_heredoc_input(filename) < 0)
	{
		unlink(filename);
		free(filename);
		return -1;
	}
	unlink(filename);
	free(filename);
	return 0;
}
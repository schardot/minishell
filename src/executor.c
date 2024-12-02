#include "../include/minishell.h"
#include "../include/libft/libft.h"
#include "../include/parser.h"
#include "../include/redirection.h"

t_exec *init_t_exec(void)
{
	t_exec *e;

	e = malloc(sizeof(t_exec));
	if (!e)
	{
		perror("malloc failed");
		return (NULL);
	}
	e->prev_fd = -1;
	e->n = 0;
	e->has_next = 0;
	return (e);
}

void handle_one(t_scmd *scmd)
{
	scmd->old_stdin_fd = dup(STDIN_FILENO);
	scmd->old_stdout_fd = dup(STDOUT_FILENO);
	if (scmd->old_stdin_fd < 0 || scmd->old_stdout_fd < 0)
	{
		perror("Failed to save original file descriptors");
		exit(EXIT_FAILURE);
	}
	if (scmd->redirect_fd_in >= 0)
	{
		if (dup2(scmd->redirect_fd_in, STDIN_FILENO) < 0)
		{
			perror("Failed to redirect stdin for builtin");
			exit(EXIT_FAILURE);
		}
		close(scmd->redirect_fd_in);
		scmd->redirect_fd_in = -1;
		if (scmd->hd_file_name)
		{
			unlink(scmd->hd_file_name);
			free(scmd->hd_file_name);
			scmd->hd_file_name = NULL;
		}
	}
	if (scmd->redirect_fd_out >= 0)
	{
		if (dup2(scmd->redirect_fd_out, STDOUT_FILENO) < 0)
		{
			perror("Failed to redirect stdout for builtin");
			exit(EXIT_FAILURE);
		}
		close(scmd->redirect_fd_out);
		scmd->redirect_fd_out = -1;
	}
}



int check_exec_command(t_tools *t, t_scmd *scmd)
{
	t_exec *e;
	struct sigaction sa_int;
	struct sigaction sa_quit;
	t_scmd *scmd_backup;
	int status_set;

	status_set = 0;
	init_sig_hand(&sa_int, &sa_quit);
	t->e = init_t_exec();
	while (scmd)
	{
		t->e->has_next = (scmd->next != NULL);
		if (create_pipe_if_needed(t, t->e->has_next, scmd) == -1)
			return (EXIT_FAILURE);
		if (!scmd->skip_exec && !scmd->heredoc_failed)
		{
			if (scmd->builtin && t->totalp == 0)
			{
				handle_one(scmd);
				t->exit_status = scmd->builtin(t, scmd);
				status_set = 1;
				restore_stdout(scmd);
				return (t->exit_status);
			}
			switch_sig_hand(&sa_int, &sa_quit, true, true);
			t->e->pid = fork();
			after_fork(t, scmd, t->e);
		}
		if(scmd->skip_exec == 1 && scmd->next  == NULL)
			status_set = 1;
		scmd = scmd->next;

	}
	if (!status_set && t->e->n > 0)
		t->exit_status = wait_for_pids(t->e->pids, t->e->n, t);
	switch_sig_hand(&sa_int, &sa_quit, false, false);
	return (t->exit_status);
}

int is_builtin(char *token)
{
	const char *func[9];
	int i;
	size_t len;

	func[0] = "cd";
	func[1] = "pwd";
	func[2] = "echo";
	func[3] = "exit";
	func[4] = "export";
	func[5] = "unset";
	func[6] = "env";
	func[7] = "history";
	func[8] = NULL;
	i = 0;
	len = ft_strlen(token);
	while (func[i] != NULL)
	{
		if (ft_strncmp(token, func[i], len) == 0 && ft_strlen(func[i]) == len)
			return (1);
		i++;
	}
	return (0);
}

char *create_full_path(char **paths, char *cmd)
{
	char *full_path;
	int i;

	i = 0;
	while (paths[i])
	{
		full_path = malloc(ft_strlen(paths[i]) + ft_strlen(cmd) + 2);
		if (!full_path)
		{
			ft_free_matrix(paths);
			return (NULL);
		}
		ft_strlcpy(full_path, paths[i], ft_strlen(paths[i]) + 1);
		ft_strlcat(full_path, "/", ft_strlen(paths[i]) + 2);
		ft_strlcat(full_path, cmd, ft_strlen(paths[i]) + ft_strlen(cmd) + 2);
		if (access(full_path, X_OK) == 0)
		{
			ft_free_matrix(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_matrix(paths);
	return (NULL);
}

char *is_executable(char *cmd, t_tools *t)
{
	char *path_env;
	char **paths;
	char *full_path;
	int i;
	struct stat path_stat;

	if (stat(cmd, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
			return (NULL);
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
	}
	path_env = ft_getenv("PATH", t);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	free(path_env);
	if (paths == NULL)
		return (NULL);
	full_path = create_full_path(paths, cmd);
	return (full_path);
}

int after_fork(t_tools *t, t_scmd *scmd, t_exec *e)
{
	if (t->e->pid == 0)
	{
		execute_child_process(t, scmd, e->prev_fd, e->has_next);
		exit(t->exit_status);
	}
	else if (t->e->pid < 0)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	else
		t->e->pids[e->n++] = t->e->pid;
	close_unused_pipes(&t->e->prev_fd, t, t->e->has_next);
	return (t->exit_status);
}

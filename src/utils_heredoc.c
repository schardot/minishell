/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:53:32 by nleite-s          #+#    #+#             */
/*   Updated: 2024/12/04 11:53:33 by nleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/libft/libft.h"
#include "../include/redirection.h"
#include <asm-generic/signal-defs.h>

int	create_heredoc_temp_file(char **filename)
{
	int	fd;

	*filename = malloc(ft_strlen(".heredoc.tmp") + 1);
	if (!*filename)
		return (-1);
	ft_strlcpy(*filename, ".heredoc.tmp", sizeof(*filename));
	fd = open(*filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		free(*filename);
		return (-1);
	}
	close(fd);
	return (0);
}

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	ft_fprintf(2, "\n");
	exit(130);
}

int	write_heredoc_input(int fd, const char *delimiter)
{
	char	*buf;

	while (1)
	{
		buf = readline("> ");
		if (!buf)
		{
			if (errno == EINTR)
				return (-1);
			break ;
		}
		if (ft_strncmp(buf, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(buf);
			break ;
		}
		if (write(fd, buf, ft_strlen(buf)) < 0 || write(fd, "\n", 1) < 0)
		{
			perror("write");
			free(buf);
			return (-1);
		}
		free(buf);
	}
	return (0);
}

int	handle_heredoc_child(const char *delimiter, char *filename)
{
	int	fd;
	int	result;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	signal(SIGINT, heredoc_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	result = write_heredoc_input(fd, delimiter);
	close(fd);
	return (result);
}

int	wait_for_heredoc_process(pid_t pid, char *filename)
{
	int	status;
	int	signal_code;

	while (waitpid(pid, &status, 0) == -1 && errno == EINTR)
		continue ;
	if (WIFSIGNALED(status))
	{
		signal_code = WTERMSIG(status);
		unlink(filename);
		return (128 + signal_code);
	}
	else if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		unlink(filename);
		return (WEXITSTATUS(status));
	}
	return (0);
}

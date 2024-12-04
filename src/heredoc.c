/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:08:13 by nleite-s          #+#    #+#             */
/*   Updated: 2024/12/04 13:56:41 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/redirection.h"
#include <asm-generic/signal-defs.h>

int	open_heredoc_file(t_scmd *node, char **filename)
{
	if (create_heredoc_temp_file(filename) < 0)
		return (-1);
	node->redirect_fd_in = open(*filename, O_RDONLY);
	if (node->redirect_fd_in < 0)
	{
		perror("open");
		free(*filename);
		return (-1);
	}
	return (0);
}

int	launch_heredoc_child(const char *delimiter, char *filename)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free(filename);
		return (-1);
	}
	else if (pid == 0)
	{
		if (handle_heredoc_child(delimiter, filename) < 0)
		{
			unlink(filename);
			exit(1);
		}
		unlink(filename);
		exit(0);
	}
	return (pid);
}

int	finalize_heredoc(pid_t pid, char *filename, int *result)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	*result = wait_for_heredoc_process(pid, filename);
	sigaction(SIGINT, &sa, NULL);
	return (0);
}

int	handle_heredoc_redirection(t_scmd *node)
{
	char	*delimiter;
	char	*filename;
	pid_t	pid;
	int		result;

	delimiter = node->r_heredoc_delimiter;
	filename = NULL;
	if (open_heredoc_file(node, &filename) < 0)
		return (-1);
	pid = launch_heredoc_child(delimiter, filename);
	if (pid < 0)
		return (-1);
	if (finalize_heredoc(pid, filename, &result) < 0)
		return (result);
	node->hd_file_name = filename;
	return (result);
}

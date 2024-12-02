/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:02:59 by nataliascha       #+#    #+#             */
/*   Updated: 2024/12/02 18:53:55 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/redirection.h"

int create_pipe_if_needed(t_tools *t, int has_next, t_scmd *scmd)
{
	(void)*scmd;
	if (has_next != 0)
	{
		if (pipe(t->pipefd) == -1)
		{
			perror("pipe");
			return (-1);
		}
	}
	return (0);
}

void setup_pipe_for_child(int prev_fd, t_tools *t, int has_next)
{
	if (prev_fd != -1)
	{
		if (dup2(prev_fd, STDIN_FILENO) < 0)
		{
			perror("Failed to redirect stdin from prev_fd");
			exit(EXIT_FAILURE);
		}
		close(prev_fd);
	}
	if (has_next)
	{
		close(t->pipefd[0]);
		if (dup2(t->pipefd[1], STDOUT_FILENO) < 0)
		{
			perror("Failed to redirect stdout to pipe");
			exit(EXIT_FAILURE);
		}
		close(t->pipefd[1]);
	}
}

void close_unused_pipes(int *prev_fd, t_tools *t, int has_next)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (has_next)
	{
		close(t->pipefd[1]);
		*prev_fd = t->pipefd[0];
	}
	else
		*prev_fd = -1;
}

void handle_redirection(t_scmd *scmd)
{
	if (scmd->redirect_fd_in >= 0)
	{
		if (dup2(scmd->redirect_fd_in, STDIN_FILENO) < 0)
		{
			perror("Failed to redirect stdin from file");
			exit(EXIT_FAILURE);
		}
		close(scmd->redirect_fd_in);

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
			perror("Failed to redirect stdout to file");
			exit(EXIT_FAILURE);
		}
		close(scmd->redirect_fd_out);
	}
}

void execute_child_process(t_tools *t, t_scmd *scmd, int prev_fd, int has_next)
{
	struct stat path_stat;

	setup_pipe_for_child(prev_fd, t, has_next);
	handle_redirection(scmd);
	scmd->exec_path = is_executable(scmd->args[0], t);
	if (scmd->builtin)
		t->exit_status = scmd->builtin(t, scmd);
	else if (scmd->exec_path)
	{
		t->exit_status = execve(scmd->exec_path, scmd->args, t->envp);
		exit(126);
	}
	else if (!ft_strchr(scmd->args[0], '/'))
	{
		ft_error(E_COMMAND_NOT_FOUND, scmd->args[0], NULL, t);
		exit(127);
	}
	else
	{
		if (stat(scmd->args[0], &path_stat) == 0)
		{
			if (S_ISDIR(path_stat.st_mode))
			{
				ft_error(E_IS_A_DIR, scmd->args[0], NULL, t);
				exit(126);
			}
			else if (access(scmd->args[0], X_OK) == -1)
			{
				ft_error(E_PERMISSION_DENIED, scmd->args[0], NULL, t);
				exit(126);
			}
		}
		else
		{
			ft_error(E_COMMAND_NOT_FOUND, scmd->args[0], NULL, t);
			exit(127);
		}
	}
}

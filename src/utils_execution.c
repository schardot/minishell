/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:05:45 by nleite-s          #+#    #+#             */
/*   Updated: 2024/12/03 20:05:46 by nleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/libft/libft.h"
#include "../include/parser.h"
#include "../include/redirection.h"

t_exec	*init_t_exec(void)
{
	t_exec	*e;

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

int	old_stdin_fd(t_scmd *scmd)
{
	scmd->old_stdin_fd = dup(STDIN_FILENO);
	scmd->old_stdout_fd = dup(STDOUT_FILENO);
	if (scmd->old_stdin_fd < 0 || scmd->old_stdout_fd < 0)
	{
		perror("Failed to save original file descriptors");
		exit(EXIT_FAILURE);
	}
	return (0);
}

void	unlink_heredoc(t_scmd *scmd)
{
	if (scmd->hd_file_name)
	{
		unlink(scmd->hd_file_name);
		free(scmd->hd_file_name);
		scmd->hd_file_name = NULL;
	}
}

void	handle_one(t_scmd *scmd)
{
	old_stdin_fd(scmd);
	if (scmd->redirect_fd_in >= 0)
	{
		if (dup2(scmd->redirect_fd_in, STDIN_FILENO) < 0)
		{
			perror("Failed to redirect stdin for builtin");
			exit(EXIT_FAILURE);
		}
		close(scmd->redirect_fd_in);
		scmd->redirect_fd_in = -1;
		unlink_heredoc(scmd);
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

int	after_fork(t_tools *t, t_scmd *scmd, t_exec *e)
{
	if (t->e->pid == 0)
	{
		execute_child_process(t, scmd, e->prev_fd, e->has_next);
		free_structs(t);
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

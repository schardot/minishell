/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:03:17 by ekechedz          #+#    #+#             */
/*   Updated: 2024/11/28 19:23:34 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/redirection.h"
#include "../include/parser.h"

void restore_stdout(t_scmd *node)
{
	if (node->old_stdin_fd >= 0)
	{
		if (dup2(node->old_stdin_fd, STDIN_FILENO) < 0)
		{
			perror("Failed to restore stdin");
			exit(EXIT_FAILURE);
		}
		// close(node->old_stdin_fd);
		// node->old_stdin_fd = -1; // Reset to avoid accidental reuse
	}

	if (node->old_stdout_fd >= 0)
	{
		if (dup2(node->old_stdout_fd, STDOUT_FILENO) < 0)
		{
			perror("Failed to restore stdout");
			exit(EXIT_FAILURE);
		}
		// close(node->old_stdout_fd);
		// node->old_stdout_fd = -1; // Reset to avoid accidental reuse
	}
}

int process_redirections(t_tools *t, t_token *tk, t_scmd *scmd)
{
	if (tk->type == INPUT)
	{
		if (access(tk->next->value, F_OK) != 0)
		{
			ft_fprintf(2, "minishell: %s: No such file or directory\n", tk->next->value);
			//perror("");
			t->exit_status = 1;
			return (t->exit_status);
		}
		else if (access(tk->next->value, R_OK) != 0)
		{
			ft_fprintf(2,"minishell: %s: Permission denied\n", tk->next->value);
			t->exit_status = 1;
			return (t->exit_status);
		}
		scmd->redirect_fd_in = open(tk->next->value, O_RDONLY);
		if (scmd->redirect_fd_in < 0)
		{
			perror("Failed to open input file");
			t->exit_status = 1;
			return (t->exit_status);
		}
	}
	if (tk->type == OUTPUT)
	{
		scmd->redirect_fd_out = open(tk->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (scmd->redirect_fd_out < 0)
		{
			perror("Failed to open output file");
			t->exit_status = 1;
			return (t->exit_status);
		}
	}
	if (tk->type == APPEND)
	{
		scmd->redirect_fd_out = open(tk->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (scmd->redirect_fd_out < 0)
		{
			perror("Failed to open append file");
			t->exit_status = 1;
			return (t->exit_status);
		}
		//printf("i oppend the file %i\n", scmd->redirect_fd_out);
	}

	return t->exit_status;
}

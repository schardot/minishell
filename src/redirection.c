/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:03:17 by ekechedz          #+#    #+#             */
/*   Updated: 2024/11/25 11:25:56 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/redirection.h"
#include "../include/parser.h"


void restore_stdout(t_scmd *node)
{
	if (dup2(node->old_stdout_fd, STDOUT_FILENO) < 0)
	{
		perror("Failed to restore STDOUT");
	}
	if (dup2(node->old_stdin_fd, STDIN_FILENO) < 0)
	{
		perror("Failed to restore STDIN");
	}
	// if (node->old_stdout_fd >= 0)
	// 	close(node->old_stdout_fd);
	// if (node->old_stdin_fd >= 0)
	// 	close(node->old_stdin_fd);
}



int process_redirections(t_token *t, t_scmd *scmd)
{
	int result = 0;

	while (t != NULL)
	{
		if (t->type == INPUT)
		{
			scmd->redirect_fd_in = open(t->next->value, O_RDONLY);
			if (access(t->next->value, F_OK) != 0)
			{
				perror("Error: Input file does not exist");
				return 1;
			}
			if (access(t->next->value, R_OK) != 0)
			{
				perror("Error: Input file is not readable");
				return 1;
			}
			if (scmd->redirect_fd_in < 0)
			{
				perror("Failed to open input file");
				return 1; // Indicate an error
			}
		}
		if (t->type == OUTPUT)
		{
			scmd->redirect_fd_out = open(t->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (scmd->redirect_fd_out < 0)
			{
				perror("Failed to open output file");
				return 1; // Indicate an error
			}
		}
		if (t->type == APPEND)
		{
			scmd->redirect_fd_out = open(t->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (scmd->redirect_fd_out < 0)
			{
				perror("Failed to open append file");
				return 1; // Indicate an error
			}
		}
		t = t->next;
	}
	return result;
}

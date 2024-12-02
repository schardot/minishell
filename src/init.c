/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 21:15:49 by ekechedz          #+#    #+#             */
/*   Updated: 2024/12/02 21:19:16 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/redirection.h"

void	init_scmd_args(t_scmd *scmd)
{
	scmd->args = NULL;
	scmd->argsc = 0;
	scmd->builtin = NULL;
	scmd->exec_path = NULL;
}

void	init_scmd_redirections(t_scmd *scmd)
{
	scmd->num_redirections = 0;
	scmd->hd_file_name = NULL;
	scmd->redirect_token = NULL;
	scmd->r_heredoc_delimiter = NULL;
	scmd->redirect_file_name = NULL;
	scmd->heredoc_failed = 0;
}

void	init_scmd_fds(t_scmd *scmd)
{
	scmd->old_stdout_fd = 0;
	scmd->old_stdin_fd = 0;
	scmd->redirect_fd_out = -1;
	scmd->redirect_fd_in = -1;
	scmd->new_fd = 0;
}

void	init_scmd_pipes(t_scmd *scmd)
{
	scmd->pipecount = 0;
	scmd->pipetotal = 0;
	scmd->skip_exec = 0;
}

void	init_scmd_next_prev(t_scmd *scmd)
{
	scmd->next = NULL;
	scmd->prev = NULL;
}

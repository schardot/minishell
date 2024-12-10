/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:37:30 by nleite-s          #+#    #+#             */
/*   Updated: 2024/12/04 11:37:31 by nleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include <unistd.h>
# include <fcntl.h>
# include "../include/parser.h"
# include "../include/minishell.h"

typedef struct s_redirection
{
	int	input_fd;
	int	output_fd;
}	t_redirection;

int		create_pipe_if_needed(t_tools *t, int has_next, t_scmd *scmd);
void	execute_child_process(t_tools *t, t_scmd *scmd, int prev_fd, \
int has_next);
void	close_unused_pipes(int *prev_fd, t_tools *t, int has_next);
void	setup_pipe_for_child(int prev_fd, t_tools *t, int has_next);
void	finalize_parent_process(int *prev_fd, t_tools *t, int has_next);
void	set_redirection(t_scmd *node, t_token *lst);
void	restore_stdout(t_scmd *node);
int		handle_heredoc_redirection(t_scmd *node);
int		wait_for_pids(pid_t *pids, int count, t_tools *t);
void	sigquit_handler(int signum);
void	switch_sig_hand(struct sigaction *sa_int, struct sigaction *sa_quit, \
bool pr_int, bool pr_quit);
int		process_redirections(t_tools *t, t_token *tk, t_scmd *scmd);

#endif

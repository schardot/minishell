/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:25:52 by nleite-s          #+#    #+#             */
/*   Updated: 2024/12/03 20:25:53 by nleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "parser.h"
# include <stdio.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>

# define MAX_INPUT_SIZE 1024
# define SYMBOL " |><"
# define MAX_COMMANDS 256

typedef enum s_error
{
	E_NO_SUCH_F,
	E_IS_A_DIR,
	E_PERMISSION_DENIED,
	E_NOT_VALID_ID,
	E_NUM_ARG_REQUIRED,
	E_TOO_MANY_ARGS,
	E_COMMAND_NOT_FOUND,
	E_HOME_NOT_SET,
	E_SYNTAX_ERROR,
	E_INVALID_OPTION,
	E_UNKNOWN_ERROR
}	t_error;

int		get_input(t_tools *t, struct sigaction *sa_int, \
struct sigaction *sa_quit);
t_tools	*init_t_tools(char **envp);
void	default_sigint_handler(int signum);
void	setup_sig_hand(struct sigaction *sa_int, struct sigaction *sa_quit);
void	switch_sig_hand(struct sigaction *sa_int, struct sigaction *sa_quit, \
bool pr_int, bool pr_quit);
void	init_sig_hand(struct sigaction *sa_int, struct sigaction *sa_quit);
void	ft_error(t_error type, char *cmd, char *inv_arg, t_tools *t);
void	restore_stdin(int saved_stdin);
int		is_directory(const char *path);

#endif

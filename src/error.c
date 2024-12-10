/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:24:44 by codespace         #+#    #+#             */
/*   Updated: 2024/12/01 15:12:49 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/libft/libft.h"
#include "../include/parser.h"
#include "../include/redirection.h"

static void	update_exit(t_error type, t_tools *t);
static char	**make_error_str(void);

void	ft_error(t_error type, char *cmd, char *inv_arg, t_tools *t)
{
	char	**err;

	err = make_error_str();
	ft_fprintf(2, "minishell: ");
	if (cmd)
		ft_fprintf(2, "%s: ", cmd);
	if (inv_arg)
	{
		if (type == E_NOT_VALID_ID)
			ft_fprintf(2, "`%s': ", inv_arg);
		else
			ft_fprintf(2, "%s: ", inv_arg);
	}
	ft_putendl_fd(err[type], 2);
	update_exit(type, t);
}

static void	update_exit(t_error ty, t_tools *t)
{
	if (ty == E_COMMAND_NOT_FOUND)
		t->exit_status = 127;
	else if (ty == E_SYNTAX_ERROR || ty == E_NUM_ARG_REQUIRED)
		t->exit_status = 2;
	else if (ty == E_NOT_VALID_ID || ty == E_NO_SUCH_F)
		t->exit_status = 127;
	else if (ty == E_TOO_MANY_ARGS || ty == E_PERMISSION_DENIED)
		t->exit_status = 1;
	else if (ty == E_IS_A_DIR)
		t->exit_status = 126;
	else
		t->exit_status = 0;
}

static char	**make_error_str(void)
{
	static char	*err[12];

	err[0] = "No such file or directory";
	err[1] = "Is a directory";
	err[2] = "Permission denied";
	err[3] = "not a valid identifier";
	err[4] = "numeric argument required";
	err[5] = "too many arguments";
	err[6] = "command not found";
	err[7] = "HOME not set";
	err[8] = "syntax error near unexpected token";
	err[9] = "invalid option";
	err[10] = "Unknown error";
	err[11] = NULL;
	return (err);
}

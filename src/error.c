/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:24:44 by codespace         #+#    #+#             */
/*   Updated: 2024/11/11 18:04:41 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/libft/libft.h"
#include "../include/parser.h"
#include "../include/redirection.h"

void	update_exit(t_error type, t_tools *t);

void	ft_error(t_error type, char *cmd, char *inv_arg, t_tools *t)
{
	static char	*err[] = {
		"No such file or directory",
		"Not a directory",
		"Permission denied",
		"not a valid identifier",
		"numeric argument required",
		"too many arguments",
		"command not found",
		"HOME not set",
		"syntax error near unexpected token",
		"Unknown error"};
	if (type != E_COMMAND_NOT_FOUND)
		ft_putstr_fd("minishell: ", 2);
	if (type != E_SYNTAX_ERROR)
		ft_putstr_fd(cmd, 2);
	if (inv_arg)
	{
		if (type != E_SYNTAX_ERROR)
		{
			if (type == E_NOT_A_VALID_ID)
				ft_putstr_fd(": `", 2);
			else
				ft_putstr_fd(": '", 2);
		}
		ft_putstr_fd(inv_arg, 2);
		ft_putstr_fd("'", 2);
	}
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(err[type], 2);
	update_exit(type, t);
}


void	update_exit(t_error type, t_tools *t)
{

	if (type == E_COMMAND_NOT_FOUND)
		t->exit_status = 127;
	else if (type == E_SYNTAX_ERROR || type == E_NUM_ARG_REQUIRED)
		t->exit_status = 2;
	else if (type == E_NOT_A_VALID_ID || type == E_NOT_A_DIR)
		t->exit_status = 1;
	else if (type == E_TOO_MANY_ARGS || type == E_PERMISSION_DENIED)
		t->exit_status = 1;
	else
		t->exit_status = 0;
}


// if type= e_syntax_error
// t-.exitsttus = 2//if (type == E_NOT_A_VALID_ID)
// 			ft_putstr_fd(": `", 2);
// 		else
// 			ft_putstr_fd(": '", 2);

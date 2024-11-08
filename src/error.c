/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:24:44 by codespace         #+#    #+#             */
/*   Updated: 2024/11/08 17:56:50 by nleite-s         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/minishell.h"
#include "../include/libft/libft.h"
#include "../include/parser.h"
#include "../include/redirection.h"

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
		"Unknown error"};
	if (type != E_COMMAND_NOT_FOUND)
	{
		ft_putstr_fd("minishell: ", 2);
	}
	ft_putstr_fd(cmd, 2);
	if (inv_arg)
	{
		if (type == E_NOT_A_VALID_ID)
			ft_putstr_fd(": `", 2);
		else
			ft_putstr_fd(": '", 2);
		ft_putstr_fd(inv_arg, 2);
		ft_putstr_fd("'", 2);
	}
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(err[type], 2);
	t->exit_status = 1;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:24:44 by codespace         #+#    #+#             */
/*   Updated: 2024/11/06 11:24:45 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		"Unknown error"};

	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	if (type == E_NOT_A_VALID_ID)
		ft_putstr_fd(": `", 2);
	else
		ft_putstr_fd(": '", 2);
	if (type == E_NOT_A_DIR || type == E_NO_SUCH_FILE || type == E_PERMISSION_DENIED || type == E_NOT_A_VALID_ID)
	{
		ft_putstr_fd(inv_arg, 2);
		ft_putstr_fd("': ", 2);
		ft_putendl_fd(err[type], 2);
	}
	t->exit_status = 1;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nataliaschardosim <nataliaschardosim@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:50:26 by nataliascha       #+#    #+#             */
/*   Updated: 2024/11/22 14:57:50 by nataliascha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/minishell.h"

static int	check_pwd_args(t_scmd *scmd, t_tools *t);

int	builtinpwd(t_tools *t, t_scmd *scmd)
{
	if (check_pwd_args(scmd, t) == 1)
		return (EXIT_FAILURE);
	if (getcwd(t->cwd, sizeof(t->cwd)))
	{
		printf("%s\n", t->cwd);
		return (EXIT_SUCCESS);
	}
	else
	{
		perror("getcwd() error");
		return (EXIT_FAILURE);
	}
}

static int	check_pwd_args(t_scmd *scmd, t_tools *t)
{
	char	*arg;

	arg = scmd->args[1];
	if (arg && arg[1] && arg[0] == '-' && arg[1] != '-')
	{
		ft_error(E_INVALID_OPTION, "pwd", arg, t);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

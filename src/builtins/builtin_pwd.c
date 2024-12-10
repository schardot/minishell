/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:50:26 by nataliascha       #+#    #+#             */
/*   Updated: 2024/12/03 20:25:46 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/minishell.h"

static int	check_pwd_args(t_scmd *scmd, t_tools *t);

int	builtinpwd(t_tools *t, t_scmd *scmd)
{
	if (check_pwd_args(scmd, t) == 2)
		return (t->exit_status);
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
		t->exit_status = 2;
		return (t->exit_status);
	}
	return (t->exit_status);
}

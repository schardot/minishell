/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:10:11 by nleite-s          #+#    #+#             */
/*   Updated: 2024/11/26 17:42:30 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"

static int	check_exit_args(t_tools *t, t_scmd *scmd);

int	builtinexit(t_tools *t, t_scmd *scmd)
{
	if (scmd->args[1])
	{
		t->exit_status = check_exit_args(t, scmd);
		if (t->exit_status != 0)
			exit (t->exit_status);
	}
	if (scmd->pipecount == 0)
	{
		printf("exit\n");
		t->exit = 1;
	}
	exit (t->exit_status);
}

static int	check_exit_args(t_tools *t, t_scmd *scmd)
{
	int	exit_stat;

	exit_stat = 0;
	if (scmd->pipecount == 0)
		printf("exit\n");
	if (ft_checkstr(scmd->args[1], &ft_isdigit) != 0)
	{
		ft_error(E_NUM_ARG_REQUIRED, "exit", scmd->args[1], t);
		return (t->exit_status);
	}
	if (scmd->argsc > 2)
	{
		ft_error(E_TOO_MANY_ARGS, "exit", scmd->args[1], t);
		return (t->exit_status);
	}
	if (ft_checkstr(scmd->args[1], &ft_isdigit) == 0)
	{
		t->exit_status = ft_atoi(scmd->args[1]);
		if (t->exit_status > 255)
			t->exit_status = t->exit_status % 256;
	}
	return (t->exit_status);
}

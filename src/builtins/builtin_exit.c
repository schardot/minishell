/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:10:11 by nleite-s          #+#    #+#             */
/*   Updated: 2024/11/25 11:21:49 by nleite-s         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../include/minishell.h"
#include "../../include/parser.h"

static int	check_exit_args(t_tools *t, t_scmd *scmd);

int	builtinexit(t_tools *t, t_scmd *scmd)
{
	int	status;

	status = 0;
	if (scmd->pipecount == 0)
	{
		printf("exit\n");
		t->exit = 1;
	}
	if (scmd->args[1])
	{
		status = check_exit_args(t, scmd);
		if (status != 0)
			exit (status);
	}
	exit (1);
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
		return (2);
	}
	if (scmd->argsc > 2)
	{
		ft_error(E_TOO_MANY_ARGS, "exit", scmd->args[1], t);
		return (2);
	}
	if (ft_checkstr(scmd->args[1], &ft_isdigit) == 0)
	{
		exit_stat = ft_atoi(scmd->args[1]);
		if (exit_stat > 256)
			exit_stat = exit_stat % 16;
	}
	return (exit_stat);
}

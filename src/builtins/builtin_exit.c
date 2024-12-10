/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:55:14 by nleite-s          #+#    #+#             */
/*   Updated: 2024/12/04 11:55:15 by nleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"

static int	check_exit_args(t_tools *t, t_scmd *scmd);

int	builtinexit(t_tools *t, t_scmd *scmd)
{
	int	status;

	if (scmd->args[1])
	{
		t->exit_status = check_exit_args(t, scmd);
		if (t->exit_status != 0 && scmd->argsc <= 2)
			exit (t->exit_status);
	}
	if (scmd->pipecount == 0 && scmd->argsc <= 2)
	{
		printf("exit\n");
		t->exit = 1;
		free_structs(t);
		status = t->exit_status;
		free_tools(t);
		exit (status);
	}
	return (t->exit_status);
}

static int	check_exit_args(t_tools *t, t_scmd *scmd)
{
	if (ft_checkstr(scmd->args[1], &ft_isdigit) != 0)
	{
		if (ft_strncmp(scmd->args[1], "--", 2))
			ft_error(E_NUM_ARG_REQUIRED, "exit", scmd->args[1], t);
		return (t->exit_status);
	}
	if (scmd->argsc > 2)
	{
		printf("exit\n");
		ft_error(E_TOO_MANY_ARGS, "exit", scmd->args[1], t);
		t->exit_status = 1;
	}
	else if (ft_checkstr(scmd->args[1], &ft_isdigit) == 0)
	{
		t->exit_status = ft_atoi(scmd->args[1]);
		if (t->exit_status > 255)
			t->exit_status = t->exit_status % 256;
	}
	return (t->exit_status);
}

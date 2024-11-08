/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:50:30 by nataliascha       #+#    #+#             */
/*   Updated: 2024/11/06 14:00:32 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/minishell.h"

int	builtinunset(t_tools *t, t_scmd *scmd)
{
	if (check_unset_args(scmd, t))
		return (EXIT_FAILURE);
	else if (scmd->args[1])
		create_new_envp(scmd, t);
	return (EXIT_SUCCESS);
}

int	check_unset_args(t_scmd *scmd, t_tools *t)
{
	int	i;
	int	j;

	j = 1;
	while (scmd->args[j])
	{
		i = 0;
		while (scmd->args[j][i])
		{
			if (!ft_isalnum(scmd->args[j][i]) && !(scmd->args[j][i] == '_'))
				ft_error(E_NOT_A_VALID_ID, scmd->args[0], scmd->args[j], t);
			i++;
		}
		j ++;
	}
	if (t->exit_status == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	create_new_envp(t_scmd *scmd, t_tools *t)
{
	const char	*var;
	int			vlen;
	int			i;

	var = scmd->args[1];
	vlen = ft_strlen(var);
	i = 0;
	while (t->envp[i])
	{
		if (ft_strncmp(t->envp[i], var, vlen) == 0 && t->envp[i][vlen] == '=')
		{
			free(t->envp[i]);
			while (t->envp[i] != NULL)
			{
				t->envp[i] = t->envp[i + 1];
				i++;
			}
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:50:30 by nataliascha       #+#    #+#             */
/*   Updated: 2024/12/03 12:03:23 by nleite-s         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../include/parser.h"
#include "../../include/minishell.h"

static int	create_new_envp(const char *var, t_tools *t);
static int	check_unset_args(t_scmd *s, t_tools *t);
static int	check_option(t_scmd *s, t_tools *t);
static void	check_argument(t_scmd *s, t_tools *t);

int	builtinunset(t_tools *t, t_scmd *scmd)
{
	int	i;

	i = 1;
	if (check_unset_args(scmd, t))
		return (t->exit_status);
	while (scmd->args[i])
	{
		create_new_envp(scmd->args[i], t);
		i ++;
	}
	return (EXIT_SUCCESS);
}

static int	check_unset_args(t_scmd *s, t_tools *t)
{
	int	i;
	int	j;

	if (check_option(s, t) == 2)
		return (t->exit_status);
	check_argument(s, t);
	if (t->exit_status == 1)
		return (t->exit_status);
	return (EXIT_SUCCESS);
}

static void	check_argument(t_scmd *s, t_tools *t)
{
	int	j;
	int	i;

	j = 1;
	while (s->args[j])
	{
		if (s->args[j][0] == '\0')
		{
			ft_error(E_NOT_VALID_ID, s->args[0], s->args[j], t);
			t->exit_status = 1;
			j++;
			continue ;
		}
		i = 0;
		while (s->args[j][i])
		{
			if (!ft_isalnum(s->args[j][i]) && !(s->args[j][i] == '_'))
			{
				ft_error(E_NOT_VALID_ID, s->args[0], s->args[j], t);
				t->exit_status = 1;
			}
			i++;
		}
		j++;
	}
}

static int	check_option(t_scmd *s, t_tools *t)
{
	if (s->args[1] && s->args[1][1] && s->args[1][0] == '-' && \
	s->args[1][1] != '-')
	{
		ft_error(E_INVALID_OPTION, "unset", s->args[1], t);
		t->exit_status = 2;
		return (t->exit_status);
	}
	return (EXIT_SUCCESS);
}

static int	create_new_envp(const char *var, t_tools *t)
{
	int			vlen;
	int			i;

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

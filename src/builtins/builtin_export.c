/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 19:55:02 by nleite-s          #+#    #+#             */
/*   Updated: 2024/12/03 19:55:04 by nleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"

static int	check_exp_args(char *arg, t_scmd *scmd, t_tools *t);
static int	print_export_list(t_tools *t);
static char	**create_var_arr(t_tools *t);
static int	export_var(t_scmd *scmd, char *full, char **spl, t_tools *t);

int	builtinexport(t_tools *t, t_scmd *scmd)
{
	char	**spl;
	char	*full;

	if (!scmd->args[1] || (ft_strlen(scmd->args[1]) == 0 && \
	(!t->parser->sq && !t->parser->dq)))
		print_export_list(t);
	else if (export_var(scmd, full, spl, t) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (t->exit_status == 1)
		return (t->exit_status);
	return (EXIT_SUCCESS);
}

static int	export_var(t_scmd *scmd, char *full, char **spl, t_tools *t)
{
	int	i;

	i = 1;
	while (scmd->args[i])
	{
		full = scmd->args[i];
		spl = ft_split(full, '=');
		if (!spl)
			return (EXIT_FAILURE);
		if (check_exp_args(scmd->args[i], scmd, t) == EXIT_SUCCESS)
		{
			if (ft_getenv(spl[0], t))
				replace_env_var(full, strlen(spl[0]), t);
			else
			{
				t->envp = ft_arrcat(t->envp, full, ft_str2dlen(t->envp));
				if (!t->envp)
					return (EXIT_FAILURE);
			}
		}
		ft_free_matrix(spl);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	check_exp_args(char *arg, t_scmd *scmd, t_tools *t)
{
	int	j;

	if ((!arg[0] && (t->parser->dq || t->parser->sq)) || (arg[0] && \
	(!ft_isalpha(arg[0]) && arg[0] != '_')))
	{
		ft_error(E_NOT_VALID_ID, "export", arg, t);
		t->exit_status = 1;
		return (t->exit_status);
	}
	j = 1;
	while (arg[j] && arg[j] != '=')
	{
		if (!ft_isalnum(arg[j]) && arg[j] != '_')
		{
			ft_error(E_NOT_VALID_ID, "export", arg, t);
			t->exit_status = 1;
			return (t->exit_status);
		}
		j++;
	}
	return (EXIT_SUCCESS);
}

static int	print_export_list(t_tools *t)
{
	size_t	i;
	char	**envcpy;
	char	*full_env;

	envcpy = create_var_arr(t);
	if (!envcpy)
		return (EXIT_FAILURE);
	i = 0;
	while (envcpy[i])
	{
		printf("declare -x %s=", envcpy[i]);
		full_env = ft_getenv(envcpy[i], t);
		if (!full_env)
		{
			printf("\n");
			break ;
		}
		printf("\"%s\"\n", full_env);
		free(full_env);
		i ++;
	}
	ft_free_matrix(envcpy);
	if (i == ft_str2dlen(t->envp))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

static char	**create_var_arr(t_tools *t)
{
	char	**sp;
	char	**sorted_envs;
	int		i;

	sorted_envs = (char **)malloc(sizeof(char *) * (ft_str2dlen(t->envp) + 1));
	if (!sorted_envs)
		return (NULL);
	i = 0;
	while (t->envp[i])
	{
		sp = ft_split(t->envp[i], '=');
		if (!sp)
			return (ft_free_matrix(sorted_envs));
		sorted_envs[i] = ft_strdup(sp[0]);
		ft_free_matrix(sp);
		if (!sorted_envs[i])
			return (ft_free_matrix(sorted_envs));
		i ++;
	}
	sorted_envs[i] = NULL;
	return (sort_arr(sorted_envs));
}

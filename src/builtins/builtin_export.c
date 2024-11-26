/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/11/26 12:11:07 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"

static int	check_exp_args(char *arg, t_scmd *scmd, t_tools *t);
static int	print_export_list(t_tools *t);
static char	**create_var_arr(t_tools *t);
static char	**sort_arr(char **arr);
void        replace_env_var(char *full, int len, t_tools *t);

int	builtinexport(t_tools *t, t_scmd *scmd)
{
	int		i;
	char	**spl;
	char	*full;

	if (!scmd->args[1])
		print_export_list(t);
	else
	{
		i = 1;
		while (scmd->args[i])
		{
			full = ft_strdup(scmd->args[i]);
			if (!full)
				return (EXIT_FAILURE);
			spl = ft_split(full, '=');
			if (!spl)
			{
				free(full);
				return (EXIT_FAILURE);
			}
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
			free(full);
			ft_free_matrix(spl);
			i++;
		}
	}
	if (t->exit_status == 1)
		return (t->exit_status);
	return (EXIT_SUCCESS);
}

static int	check_exp_args(char *arg, t_scmd *scmd, t_tools *t)
{
	int	j;

	if (!arg[0] || (!ft_isalpha(arg[0]) && arg[0] != '_'))
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
	envcpy = sort_arr(envcpy);
	i = 0;
	while (envcpy[i])
	{
		printf("declare -x %s=", envcpy[i]);
		full_env = ft_getenv(envcpy[i], t);
		if (!full_env)
			break ;
		printf("\"%s\"\n", full_env);
		free(envcpy[i]);
		i++;
	}
	free (envcpy);
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
		{
			ft_free_matrix(sorted_envs);
			return (NULL);
		}
		sorted_envs[i] = ft_strdup(sp[0]);
		ft_free_matrix(sp);
		if (!sorted_envs[i])
		{
			ft_free_matrix(sorted_envs);
			return (NULL);
		}
		i ++;
	}
	sorted_envs[i] = NULL;
	return (sorted_envs);
}

static char	**sort_arr(char **arr)
{
	char	*swp;
	int		i;
	int		j;

	i = 0;
	while (arr[i])
	{
		j = i + 1;
		while (arr[j])
		{
			if (ft_strncmp(arr[i], arr[j], strlen(arr[i])) > 0)
			{
				swp = arr[i];
				arr[i] = arr[j];
				arr[j] = swp;
			}
			j ++;
		}
		i ++;
	}
	return (arr);
}

void	replace_env_var(char *full, int len, t_tools *t)
{
	int	i;

	i = 0;
	while (t->envp[i])
	{
		if (ft_strncmp(full, t->envp[i], len) == 0 && t->envp[i][len] == '=')
		{
			free (t->envp[i]);
			t->envp[i] = ft_strdup(full);
			if (!t->envp[i])
			{
				printf("error allocating");
				return ;
			}
			return ;
		}
		i ++;
	}
}

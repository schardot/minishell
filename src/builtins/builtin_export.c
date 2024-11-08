/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:02:23 by codespace         #+#    #+#             */
/*   Updated: 2024/11/08 19:09:47 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"

static int	check_exp_args(char *arg, t_scmd *scmd, t_tools *t);
static int	print_export_list(t_tools *t);
static char	**create_var_arr(t_tools *t);
static char	**sort_arr(char **arr);

int	builtinexport(t_tools *t, t_scmd *scmd)
{
	int	i;
	char	*arg;

	if (!scmd->args[1])
		print_export_list(t);
	else
	{
		i = 1;
		while (scmd->args[i])
		{
			arg = ft_strdup(scmd->args[i]);
			if (check_exp_args(scmd->args[i], scmd, t) == 0)
			{
				//printf("last before arrcat: \"%s\" and this it what should be appended: \"%s\"\n", t->envp[ft_str2dlen(t->envp)], scmd->args[i]);
				t->envp = ft_arrcat(t->envp, arg, ft_str2dlen(t->envp));
				//printf("last after arrcat: \"%s\" and this it what should have been appended: \"%s\"\n", t->envp[ft_str2dlen(t->envp)-1], arg);
				if (!t->envp)
					return (EXIT_FAILURE);
			}
			i ++;
		}
	}
	if (t->exit_status == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	check_exp_args(char *arg, t_scmd *scmd, t_tools *t)
{
	int	i;

	i = 0;
	if (arg[i] == '=')
	{
		ft_error(E_NOT_A_VALID_ID, "export", scmd->args[1], t);
		return (EXIT_FAILURE);
	}
	while (arg[i])
	{
		if (!ft_isalpha(arg[i]) && arg[i] != '=')
		{
			ft_error(E_NOT_A_VALID_ID, "export", scmd->args[1], t);
			return (EXIT_FAILURE);
		}
		i ++;
	}
	return (EXIT_SUCCESS);
}

static int	print_export_list(t_tools *t)
{
	int		i;
	char	**envcpy;
	char	*full_env;

	envcpy = create_var_arr(t);
	if (!envcpy)
		return (EXIT_FAILURE);
	envcpy = sort_arr(envcpy);
	i = 0;
	while (envcpy[i])
	{
		printf("declare -x ");
		full_env = ft_getenv(envcpy[i], t);
		if (!full_env)
			break ;
		printf("%s\n", full_env);
		i++;
	}
	if (i == ft_str2dlen(t->envp))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

static char	**create_var_arr(t_tools *t)
{
	char		**sp;
	char		**sorted_envs;
	int			i;

	sorted_envs = (char **)malloc(sizeof(char *) * ft_str2dlen(t->envp));
	if (!sorted_envs)
		return (NULL);
	i = 0;
	while (t->envp[i])
	{
		sp = ft_split(t->envp[i], '=');
		if (!sp)
			return (NULL);
		sorted_envs[i] = ft_strdup(sp[0]);
		if (!sorted_envs[i++])
			return (NULL);
	}
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
			if (ft_strncmp(arr[i], arr[j], 100000000) > 0)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:06:14 by ekechedz          #+#    #+#             */
/*   Updated: 2024/12/04 14:06:22 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"

static int	print_export_list(t_tools *t);
static char	**create_var_arr(t_tools *t);

int	builtinexport(t_tools *t, t_scmd *scmd)
{
	char	**spl;
	char	*full;

	spl = NULL;
	full = NULL;
	if (!scmd->args[1] || (ft_strlen(scmd->args[1]) == 0 && \
	(!t->parser->sq && !t->parser->dq)))
		print_export_list(t);
	else if (export_var(scmd, full, spl, t) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (t->exit_status == 1)
		return (t->exit_status);
	return (EXIT_SUCCESS);
}

int	check_exp_args(char *arg, t_scmd *scmd, t_tools *t)
{
	int	j;

	(void)scmd;
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

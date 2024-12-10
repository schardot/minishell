/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:06:45 by ekechedz          #+#    #+#             */
/*   Updated: 2024/12/04 14:06:48 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"

char	**sort_arr(char **arr)
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
			if (ft_strncmp(arr[i], arr[j], ft_strlen(arr[i])) > 0)
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
				free(full);
				return ;
			}
			free(full);
			return ;
		}
		i ++;
	}
	free(full);
}

int	export_var(t_scmd *scmd, char *full, char **spl, t_tools *t)
{
	int	i;

	i = 0;
	(void)full;
	(void)spl;
	while (scmd->args[i])
	{
		if (process_export_var(scmd->args[i], t) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	process_export_var(char *arg, t_tools *t)
{
	char	**spl;
	char	*existing_var;

	spl = ft_split(arg, '=');
	if (!spl)
		return (EXIT_FAILURE);
	if (check_exp_args(arg, NULL, t) != EXIT_SUCCESS)
		return (ft_free_matrix(spl), EXIT_SUCCESS);
	existing_var = ft_getenv(spl[0], t);
	if (existing_var)
	{
		replace_env_var(ft_strdup(arg), ft_strlen(spl[0]), t);
		free(existing_var);
	}
	else
	{
		t->envp = ft_arrcat(t->envp, arg, ft_str2dlen(t->envp));
		if (!t->envp)
			return (ft_free_matrix(spl), EXIT_FAILURE);
	}
	ft_free_matrix(spl);
	return (EXIT_SUCCESS);
}

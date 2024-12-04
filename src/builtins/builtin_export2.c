/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:54:33 by nleite-s          #+#    #+#             */
/*   Updated: 2024/12/04 12:47:10 by nleite-s         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

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
			return ;
		}
		i ++;
	}
}

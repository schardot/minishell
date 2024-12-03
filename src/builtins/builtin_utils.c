/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:49:13 by nataliascha       #+#    #+#             */
/*   Updated: 2024/12/03 20:52:01 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include <sys/stat.h>

int	builtinhistory(t_tools *t, t_scmd *node)
{
	HIST_ENTRY	**list;
	int			i;

	(void)*t;
	(void)*node;
	list = history_list();
	if (list)
	{
		i = 0;
		while (list[i])
		{
			printf("%d %s\n", i + history_base, list[i]->line);
			i ++;
		}
	}
	return (EXIT_SUCCESS);
}

char	*ft_getenv(char *env, t_tools *t)
{
	int	env_len;
	int	i;

	i = 0;
	env_len = ft_strlen(env);
	while (t->envp[i])
	{
		if (ft_strncmp(env, t->envp[i], env_len) == 0)
		{
			if (t->envp[i][env_len] == '=')
				return (ft_strdup(t->envp[i] + env_len + 1));
		}
		i++;
	}
	return (NULL);
}

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
	{
		perror("stat");
		return (-1);
	}
	return (S_ISDIR(path_stat.st_mode));
}

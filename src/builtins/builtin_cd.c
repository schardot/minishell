/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:50:05 by nataliascha       #+#    #+#             */
/*   Updated: 2024/11/11 17:36:06 by nleite-s         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/redirection.h"
#include <sys/stat.h>

static int	check_cd_errors(char *path, t_scmd *node, t_tools *t);

int	builtincd(t_tools *t, t_scmd *node)
{
	char	*path;

	(void)t;
	if (!node->args[1])
	{
		path = ft_getenv("HOME", t);
		if (!path)
        {
            ft_error(E_HOME_NOT_SET, "cd", NULL, t);
            return (EXIT_FAILURE);
        }
	}
	else
    {
        // if (node->args[1][0] == '$')
        //     path = ft_getenv(node->args[1], t);
        // else
            path = trim_quotes(node->args[1], true);
    }
	if (check_cd_errors(path, node, t))
		return (EXIT_FAILURE);
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	check_cd_errors(char *path, t_scmd *node, t_tools *t)
{
	struct stat	path_stat;

	if (access(path, F_OK) != 0 || access(path, X_OK) != 0)
	{
		if (access(path, F_OK) != 0)
			ft_error(E_NO_SUCH_FILE, node->args[0], path, t);
		else if (access(path, X_OK) != 0)
			ft_error(E_PERMISSION_DENIED, node->args[0], path, t);
		return (EXIT_FAILURE);
	}
	if (stat(path, &path_stat) != 0 || !S_ISDIR(path_stat.st_mode))
	{
		ft_error(E_NOT_A_DIR, node->args[0], path, t);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

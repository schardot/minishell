/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:50:05 by nataliascha       #+#    #+#             */
/*   Updated: 2024/11/08 19:08:18 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			return (EXIT_FAILURE);
	}
	else
		path = node->args[1];
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
			ft_error(E_NO_SUCH_FILE, node->args[0], node->args[1], t);
		else if (access(path, X_OK) != 0)
			ft_error(E_PERMISSION_DENIED, node->args[0], node->args[1], t);
		return (EXIT_FAILURE);
	}
	if (stat(path, &path_stat) != 0 || !S_ISDIR(path_stat.st_mode))
	{
		ft_error(E_NOT_A_DIR, node->args[0], node->args[1], t);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

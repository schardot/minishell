/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nataliaschardosim <nataliaschardosim@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:50:05 by nataliascha       #+#    #+#             */
/*   Updated: 2024/11/22 14:41:51 by nataliascha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/redirection.h"
#include <sys/stat.h>

static int	check_cd_errors(char *path, t_scmd *scmd, t_tools *t);
static int	check_cd_args(char **path, t_scmd *scmd, t_tools *t);

int	builtincd(t_tools *t, t_scmd *scmd)
{
	char	*path;

	if (check_cd_args(&path, scmd, t) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (check_cd_errors(path, scmd, t) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		return (EXIT_FAILURE);
	}
	if (!getcwd(t->cwd, sizeof(t->cwd)))
	{
		perror("minishell: cd");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	check_cd_errors(char *path, t_scmd *scmd, t_tools *t)
{
	struct stat	path_stat;

	if (access(path, F_OK) != 0)
	{
		ft_error(E_NO_SUCH_FILE, scmd->args[0], path, t);
		return (EXIT_FAILURE);
	}
	if (stat(path, &path_stat) != 0 || !S_ISDIR(path_stat.st_mode))
	{
		ft_error(E_NOT_A_DIR, scmd->args[0], path, t);
		return (EXIT_FAILURE);
	}
	if (access(path, X_OK) != 0)
	{
		ft_error(E_PERMISSION_DENIED, scmd->args[0], path, t);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	check_cd_args(char **path, t_scmd *scmd, t_tools *t)
{
	if (!scmd->args[1])
	{
		*path = ft_getenv("HOME", t);
		if (!*path)
		{
			ft_error(E_HOME_NOT_SET, "cd", NULL, t);
			return (EXIT_FAILURE);
		}
	}
	else
		*path = trim_quotes(scmd->args[1]);
	return (EXIT_SUCCESS);
}

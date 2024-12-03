/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:02:05 by nleite-s          #+#    #+#             */
/*   Updated: 2024/12/03 20:02:06 by nleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/redirection.h"
#include <sys/stat.h>

static int	check_cd_errors(char *path, t_scmd *scmd, t_tools *t);
static int	check_cd_args(char **path, t_scmd *scmd, t_tools *t);
static int	check_cd(t_tools *t);

int	builtincd(t_tools *t, t_scmd *scmd)
{
	char	*path;

	if (check_cd_args(&path, scmd, t) != 0)
		return (t->exit_status);
	if (check_cd_errors(path, scmd, t) != EXIT_SUCCESS)
	{
		free (path);
		path = NULL;
		return (EXIT_FAILURE);
	}
	if (chdir(path) != 0)
	{
		free (path);
		path = NULL;
		perror("minishell: cd");
		t->exit_status = 1;
		return (t->exit_status);
	}
	free (path);
	path = NULL;
	return (check_cd(t));
}

static int	check_cd(t_tools *t)
{
	if (!getcwd(t->cwd, sizeof(t->cwd)))
	{
		perror("minishell: cd");
		t->exit_status = 1;
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	check_cd_errors(char *path, t_scmd *scmd, t_tools *t)
{
	struct stat	path_stat;

	if (access(path, F_OK) != 0)
	{
		ft_error(E_NO_SUCH_F, scmd->args[0], path, t);
		return (EXIT_FAILURE);
	}
	if (stat(path, &path_stat) != 0 || !S_ISDIR(path_stat.st_mode))
	{
		ft_error(E_IS_A_DIR, scmd->args[0], path, t);
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
	else if (scmd->args[2])
	{
		ft_fprintf(2, "minishell: %s: too many arguments\n", scmd->args[0]);
		t->exit_status = 1;
		return (t->exit_status);
	}
	else
		*path = ft_strdup(scmd->args[1]);
	return (EXIT_SUCCESS);
}

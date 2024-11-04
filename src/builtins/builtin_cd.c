/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:50:05 by nataliascha       #+#    #+#             */
/*   Updated: 2024/11/04 16:44:02 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/redirection.h"

int builtincd(t_tools *t, t_scmd *node)
{
	char *path;
	char cwd[PATH_MAX];

	// If no arguments are provided, change to HOME directory
	if (!node->args[1])
	{
		path = getenv("HOME");
		if (!path)
		{
			printf("Error: HOME environment variable not set\n");
			return (EXIT_FAILURE);
		}
	}
	else
	{
		path = node->args[1];
	}

	// Change directory and handle errors
	if (chdir(path) != 0)
	{
		printf("Error: %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}

	// Update PWD environment variable
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		setenv("OLDPWD", getenv("PWD"), 1);
		setenv("PWD", cwd, 1);
	}
	else
	{
		printf("Error: Unable to update current directory\n");
		return (EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}

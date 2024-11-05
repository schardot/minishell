/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:50:05 by nataliascha       #+#    #+#             */
/*   Updated: 2024/11/04 17:08:03 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/redirection.h"

int	builtincd(t_tools *t, t_scmd *node)
{
	char	*path;
	char	cwd[PATH_MAX];

	if (!node->args[1])
	{
		path = getenv("HOME");
		if (!path)
			return (EXIT_FAILURE);
	}
	else
		path = node->args[1];
	if (chdir(path) != 0)
	{
		printf("Error: %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

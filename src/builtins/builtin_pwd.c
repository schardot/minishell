/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:50:26 by nataliascha       #+#    #+#             */
/*   Updated: 2024/11/06 08:54:29 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

int	builtinpwd(t_tools *t, t_scmd *node)
{
	char	buffer[PATH_MAX];

	if (getcwd(buffer, sizeof(buffer)))
	{
		printf("%s\n", buffer);
		return (EXIT_SUCCESS);
	}
	else
	{
		perror("getcwd() error");
		return (EXIT_FAILURE);
	}
}

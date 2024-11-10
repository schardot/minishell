/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:50:26 by nataliascha       #+#    #+#             */
/*   Updated: 2024/11/10 11:47:06 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

int	builtinpwd(t_tools *t, t_scmd *node)
{
	char	buffer[PATH_MAX];
	(void)*t;
	(void)*node;

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

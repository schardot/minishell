/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nataliaschardosim <nataliaschardosim@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:50:26 by nataliascha       #+#    #+#             */
/*   Updated: 2024/11/01 10:50:27 by nataliascha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/redirection.h"

int	builtinpwd(t_tools *t, t_scmd *node)
{
	(void)t;
	(void)node;
	char buffer[PATH_MAX];

	if (getcwd(buffer, sizeof(buffer)))
		printf("%s\n", buffer);
	else
		perror("getcwd() error");
	return (EXIT_SUCESS);
}
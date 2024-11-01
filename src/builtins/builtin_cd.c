/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nataliaschardosim <nataliaschardosim@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:50:05 by nataliascha       #+#    #+#             */
/*   Updated: 2024/11/01 10:50:07 by nataliascha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/redirection.h"

int	builtincd(t_tools *t, t_scmd *node)
{
	if (chdir(node->args[1]) != 0)
		printf("Error: %s\n", strerror(errno));
	return (EXIT_SUCESS);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nataliaschardosim <nataliaschardosim@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:50:19 by nataliascha       #+#    #+#             */
/*   Updated: 2024/11/01 10:50:20 by nataliascha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/redirection.h"

int	builtinenv(t_tools *t, t_scmd *node)
{
	int	i;

	i = 0;
	while(t->envp[i])
	{
		printf("%s\n", t->envp[i]);
		i ++;
	}
	return (EXIT_SUCESS);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:50:19 by nataliascha       #+#    #+#             */
/*   Updated: 2024/11/06 08:51:18 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"

int	builtinenv(t_tools *t, t_scmd *scmd)
{
	int	i;

	i = 0;
	// if (scmd->args[1])
	// {
	//     printf("env: '%s': No such file or directory\n", scmd->args[1]);
	//     return (EXIT_FAILURE);
	// }
	while(t->envp[i])
	{
		printf("%s\n", t->envp[i]);
		i ++;
	}
	return (EXIT_SUCCESS);
}

/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:50:19 by nataliascha       #+#    #+#             */
/*   Updated: 2024/11/07 11:49:10 by nleite-s         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../include/minishell.h"
#include "../../include/parser.h"

int	builtinenv(t_tools *t, t_scmd *scmd)
{
	int	i;
	
	i = 0;
	if (scmd->args[1])
	{
		ft_error(E_NO_SUCH_FILE, "env", scmd->args[1], t);
		return (EXIT_FAILURE);
	}
	if (scmd->pipecount == 0)
		t->pipefd[0] = STDOUT_FILENO;
	printf("in env: %d\n", t->pipefd[0]);
	while (t->envp[i])
	{
		ft_putendl_fd(t->envp[i], t->pipefd[0]);
		i ++;
	}
	return (EXIT_SUCCESS);
}


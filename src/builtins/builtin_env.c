/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nataliaschardosim <nataliaschardosim@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:50:03 by nataliascha       #+#    #+#             */
/*   Updated: 2024/11/22 16:36:49 by nataliascha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"

int	builtinenv(t_tools *t, t_scmd *scmd)
{
	int	i;

	i = 0;
	if (scmd->args[1])
	{
		ft_error(E_NO_SUCH_F, "env", scmd->args[1], t);
		return (t->exit_status);
	}
	if (scmd->pipecount == 0)
		t->pipefd[0] = STDOUT_FILENO;
	while (t->envp[i])
	{
		if (ft_strchr(t->envp[i], '=') && t->envp[i][0] != '=')
			ft_putendl_fd(t->envp[i], t->pipefd[0]);
		i ++;
	}
	return (t->exit_status);
}

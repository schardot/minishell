/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nataliaschardosim <nataliaschardosim@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:00:48 by nataliascha       #+#    #+#             */
/*   Updated: 2024/12/01 19:09:40 by nataliascha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"
#include "../include/minishell.h"
#include "../include/redirection.h"

int	wait_for_pids(pid_t *pids, int count, t_tools *t)
{
	int	status;
	int	last_exit;
	int	i;

	i = 0;
	last_exit = 0;
	while (i < count)
	{
		if (waitpid(pids[i], &status, 0) == -1)
		{
			perror("waitpid");
			return (EXIT_FAILURE);
		}
		else if (WIFEXITED(status))
			last_exit = WEXITSTATUS(status);
		else if (WTERMSIG(status) == SIGINT)
			last_exit = 130;
		else if (WTERMSIG(status) == SIGQUIT)
			last_exit = 131;
		else
			last_exit = 1;
		i++;
	}
	return (last_exit);
}

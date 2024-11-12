/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:50:12 by nataliascha       #+#    #+#             */
/*   Updated: 2024/11/12 17:30:24 by nleite-s         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/redirection.h"

int	builtinecho(t_tools *t, t_scmd *scmd)
{
	int		i;
	int		newline;
	(void)*t;

	i = 1;
	newline = 1;
	while (i < scmd->argsc && scmd->args[i][0] == '-' && scmd->args[i][1] == 'n')
	{
		int j = 1;
		while (scmd->args[i][j] == 'n')
			j++;
		if (scmd->args[i][j] != '\0')
			break ;
		newline = 0;
		i++;
	}
	while (i < scmd->argsc)
	{
		ft_putstr_fd(scmd->args[i], 1);
		if (i != scmd->argsc - 1)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", 1);
	restore_stdout(scmd);
	return (EXIT_SUCCESS);
}

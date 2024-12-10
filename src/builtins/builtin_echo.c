/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:03:23 by nleite-s          #+#    #+#             */
/*   Updated: 2024/12/03 20:03:24 by nleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/redirection.h"

static int	check_newline(char **args, int argsc, int *i);

int	builtinecho(t_tools *t, t_scmd *scmd)
{
	int		i;
	int		newline;

	(void)*t;
	i = 1;
	newline = check_newline(scmd->args, scmd->argsc, &i);
	while (i < scmd->argsc)
	{
		if (ft_strncmp(scmd->args[i], "\"\"", 2) && \
		ft_strncmp(scmd->args[i], "''", 2))
			ft_putstr_fd(scmd->args[i], 1);
		if (i != scmd->argsc - 1)
			ft_putchar_fd(' ', 1);
		i ++;
	}
	if (newline)
		ft_putstr_fd("\n", 1);
	return (EXIT_SUCCESS);
}

static int	check_newline(char **args, int argsc, int *i)
{
	int	j;
	int	newline;

	newline = 1;
	while (*i < argsc && args[*i][0] == '-' && args[*i][1] == 'n')
	{
		j = 1;
		while (args[*i][j] == 'n')
			j++;
		if (args[*i][j] != '\0')
			break ;
		newline = 0;
		(*i)++;
	}
	return (newline);
}

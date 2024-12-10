/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 21:22:39 by ekechedz          #+#    #+#             */
/*   Updated: 2024/12/02 21:28:12 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/redirection.h"

t_scmd	*scmd_new(void)
{
	t_scmd	*scmd;

	scmd = malloc(sizeof(t_scmd));
	if (!scmd)
		return (NULL);
	init_scmd_args(scmd);
	init_scmd_redirections(scmd);
	init_scmd_fds(scmd);
	init_scmd_pipes(scmd);
	init_scmd_next_prev(scmd);
	return (scmd);
}

int	(*get_builtin_function(char *command))(t_tools *t, t_scmd *s)
{
	int	len;

	len = ft_strlen(command);
	if (!ft_strncmp(command, "cd", len))
		return (&builtincd);
	else if (!ft_strncmp(command, "echo", len))
		return (&builtinecho);
	else if (!ft_strncmp(command, "pwd", len))
		return (&builtinpwd);
	else if (!ft_strncmp(command, "export", len))
		return (&builtinexport);
	else if (!ft_strncmp(command, "unset", len))
		return (&builtinunset);
	else if (!ft_strncmp(command, "env", len))
		return (&builtinenv);
	else if (!ft_strncmp(command, "exit", len))
		return (&builtinexit);
	else if (!ft_strncmp(command, "history", len))
		return (&builtinhistory);
	return (NULL);
}

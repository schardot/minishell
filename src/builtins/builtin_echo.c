/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:50:12 by nataliascha       #+#    #+#             */
/*   Updated: 2024/11/09 20:03:30 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/redirection.h"

int	builtinecho(t_tools *t, t_scmd *scmd)
{
	int		flag;
	char	*arg;
	char	*temp;
	int		i;

    // i = 0;
    // if (i == 1)
	//handle_redirection(scmd);
	// if (!scmd->args[1])
	// 	printf("\n");
    if (scmd->args[1] && !ft_strncmp(scmd->args[1], "-n", ft_strlen(scmd->args[1])))
        flag = 1;
	else
		flag = 0;
	i = flag + 1;
	arg = ft_strdup("");
	while (scmd->args[i])
	{
		temp = ft_strjoin(arg, scmd->args[i]);
		arg = temp;
		if (scmd->args[i + 1])
		{
			temp = ft_strjoin(arg, " ");
			arg = temp;
		}
		i++;
	}
	ft_putstr_fd(arg, STDOUT_FILENO);
	if (!flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
    return (EXIT_SUCCESS);
}

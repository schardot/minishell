/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nataliaschardosim <nataliaschardosim@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:50:12 by nataliascha       #+#    #+#             */
/*   Updated: 2024/11/02 12:57:52 by nataliascha      ###   ########.fr       */
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

	handle_redirection(scmd);
	if (!scmd->args[1])
		printf("\n");
	if (!ft_strncmp(scmd->args[1], "-n", ft_strlen(scmd->args[1])))
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
	restore_stdout(scmd);
	return (EXIT_SUCCESS);
}

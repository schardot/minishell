/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:50:12 by nataliascha       #+#    #+#             */
/*   Updated: 2024/11/11 17:08:22 by nleite-s         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/redirection.h"

int	check_echo_args(t_scmd *scmd);

int	builtinecho(t_tools *t, t_scmd *scmd)
{
	//int		newline;
	char	*arg;
	int		i;
	(void)*t;

	// if (scmd->args[1] && !ft_strncmp(scmd->args[1], "-n", ft_strlen(scmd->args[1])))
	// 	newline = 1;
	// else
	// 	newline = 0;
	if (!scmd->args[1])
	{
		ft_putstr_fd("\n", 1);
		return (EXIT_SUCCESS);
	}
	i = 1;
	if (scmd->args[1] && ft_strncmp(scmd->args[1], "-n", ft_strlen(scmd->args[1])) == 0)
		i ++;
	while (i < scmd->argsc)
	{
		arg = trim_quotes(scmd->args[i], true);
		ft_putstr_fd(arg, 0);
		if (i != scmd->argsc - 1)
			ft_putchar_fd(' ', 1);
		i ++;
	}
	if (scmd->args[1] && ft_strncmp(scmd->args[1], "-n", ft_strlen(scmd->args[1])) != 0)
		ft_putstr_fd("\n", 1);
	restore_stdout(scmd);
	return (EXIT_SUCCESS);
}


/*
Permission Denied Errors (in rare cases when redirecting output):
Example: echo "Hello" > /root/hello.txt
If you try to redirect echo output to a file or directory where you
lack write permissions,bash will return a "Permission denied" error
for the redirection, not echo itself. This is an error from
the shell related to file permissions rather than from echo.

Invalid Redirections:
Example: echo "Hello" > /dev/full
If you attempt to write to a device like /dev/full, which always
acts as a "full" storage, bash will output an error (e.g., No space
 left on device), even though echo itself works.

Command Substitution Errors:
Example: echo $(undefined_command)
If echo is used with command substitution (e.g., echo $(command)),
 and the command inside substitution fails or doesn’t exist, bash
  will throw an error like command not found.*/

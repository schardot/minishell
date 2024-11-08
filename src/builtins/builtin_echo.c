/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:50:12 by nataliascha       #+#    #+#             */
/*   Updated: 2024/11/08 11:54:34 by nleite-s         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/redirection.h"

static char	*create_arg(t_scmd *scmd, int newline);

int	builtinecho(t_tools *t, t_scmd *scmd)
{
	int		newline;
	char	*arg;
	int		i;

	handle_redirection(scmd);
	if (!scmd->args[1])
		printf("\n");
	if (!ft_strncmp(scmd->args[1], "-n", ft_strlen(scmd->args[1])))
		newline = 1;
	else
		newline = 0;
	arg = create_arg(scmd, newline);
	ft_putstr_fd(arg, STDOUT_FILENO);
	// if (scmd->pipecount == 0)
	// 	t->pipefd[0] = STDOUT_FILENO;
	// ft_putstr_fd(arg, t->pipefd[0]);
	if (!newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	if (t->pipefd[0] == 0)
		restore_stdout(scmd);
	return (EXIT_SUCCESS);
}

static char	*create_arg(t_scmd *scmd, int newline)
{
	char	*temp;
	char	*arg;
	int		i;

	i = newline + 1;
	arg = ft_strdup("");
	if (!arg)
		return (NULL);
	while (scmd->args[i])
	{
		temp = ft_strjoin(arg, scmd->args[i]);
		if (!temp)
			return (NULL);
		arg = temp;
		if (scmd->args[i + 1])
		{
			temp = ft_strjoin(arg, " ");
			arg = temp;
		}
		i++;
	}
	return (arg);
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

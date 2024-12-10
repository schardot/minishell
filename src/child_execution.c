/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 20:26:02 by ekechedz          #+#    #+#             */
/*   Updated: 2024/12/02 20:29:48 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/redirection.h"

void	handle_directory_or_permission(t_tools *t, char *cmd)
{
	struct stat	path_stat;

	if (stat(cmd, &path_stat) == 0)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			ft_error(E_IS_A_DIR, cmd, NULL, t);
			exit(126);
		}
		else if (access(cmd, X_OK) == -1)
		{
			ft_error(E_PERMISSION_DENIED, cmd, NULL, t);
			exit(126);
		}
	}
	else
	{
		ft_error(E_COMMAND_NOT_FOUND, cmd, NULL, t);
		exit(127);
	}
}

void	handle_command_not_found(t_tools *t, t_scmd *scmd)
{
	if (!ft_strchr(scmd->args[0], '/'))
	{
		ft_error(E_COMMAND_NOT_FOUND, scmd->args[0], NULL, t);
		exit(127);
	}
	else
	{
		handle_directory_or_permission(t, scmd->args[0]);
	}
}

void	handle_builtin_or_exec(t_tools *t, t_scmd *scmd)
{
	if (scmd->builtin)
		t->exit_status = scmd->builtin(t, scmd);
	else if (scmd->exec_path)
	{
		t->exit_status = execve(scmd->exec_path, scmd->args, t->envp);
		exit(126);
	}
	else
	{
		handle_command_not_found(t, scmd);
	}
}

void	handle_command_execution(t_tools *t, t_scmd *scmd)
{
	handle_builtin_or_exec(t, scmd);
}

void	execute_child_process(t_tools *t,
								t_scmd *scmd, int prev_fd, int has_next)
{
	setup_pipe_for_child(prev_fd, t, has_next);
	handle_redirection(scmd);
	scmd->exec_path = is_executable(scmd->args[0], t);
	handle_command_execution(t, scmd);
}

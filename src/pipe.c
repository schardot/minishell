#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/redirection.h"

int create_pipe_if_needed(t_tools *t, int has_next, t_scmd *scmd)
{
	(void)*scmd;
	if (has_next != 0)
	{
		if (pipe(t->pipefd) == -1)
		{
			perror("pipe");
			return -1;
		}
	}
	return 0;
}

void setup_pipe_for_child(int prev_fd, t_tools *t, int has_next)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (has_next)
	{
		close(t->pipefd[0]);
		dup2(t->pipefd[1], STDOUT_FILENO);
		close(t->pipefd[1]);
	}
}

void close_unused_pipes(int *prev_fd, t_tools *t, int has_next)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (has_next)
	{
		close(t->pipefd[1]);
		*prev_fd = t->pipefd[0];
	}
	else
		*prev_fd = -1;
}

void execute_child_process(t_tools *t, t_scmd *scmd, int prev_fd, int has_next)
{
	int result;

	result = handle_redirection(scmd);
	setup_pipe_for_child(prev_fd, t, has_next);
	if (result != 0)
	{
		t->exit_status = result;
		exit(t->exit_status);
	}
	if (is_executable(scmd->args[0], t))
	{
		scmd->exec_path = is_executable(scmd->args[0], t);
		execve(scmd->exec_path, scmd->args, t->envp);
		ft_error(E_COMMAND_NOT_FOUND, scmd->args[0], NULL, t);
		exit(t->exit_status);
	}
	else
	{
		//printf("before%d\n", t->exit_status);
		ft_error(E_COMMAND_NOT_FOUND, scmd->args[0], NULL, t);
		//printf("after%d\n", t->exit_status);
		//printf("minishell: command not found: %s\n", scmd->args[0]);
		exit(t->exit_status);
		// printf("after exit %d\n", t->exit_status);
  }
}

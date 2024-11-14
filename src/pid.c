#include "../include/parser.h"
#include "../include/minishell.h"
#include "../include/redirection.h"

int wait_for_pids(pid_t *pids, int count, t_tools *t)
{
	int status;
	int last_exit = 0;
	for (int i = 0; i < count; i++)
	{
		if (waitpid(pids[i], &status, 0) == -1)
		{
			perror("waitpid");
			return EXIT_FAILURE;
		}
		// Update exit status based on each child's outcome
		if (WIFEXITED(status))
		{
			last_exit = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			last_exit = 128 + WTERMSIG(status);
		}
	}
	t->exit_status = last_exit;
	return t->exit_status;
}

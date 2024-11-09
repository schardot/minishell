#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/redirection.h"
#include "../../include/minishell.h"
#include "../../include/parser.h"

static int check_exit_args(t_tools *t, t_scmd *scmd);

int builtinexit(t_tools *t, t_scmd *scmd)
{
	int status;

	status = 0;
	if (scmd->pipecount == 0)
			printf("exit\n");
	if (scmd->args[1])
	{
		status = check_exit_args(t, scmd);
		if (status != 0)
			exit (status);
	}
	exit (1);
}

static int check_exit_args(t_tools *t, t_scmd *scmd)
{
	int exit_stat;

	if (scmd->pipecount == 0)
		printf("exit\n"); //is it on stdout or stderr?
	if (ft_checkstr(scmd->args[1], &ft_isdigit) != 0)
	{
		ft_error(E_NUM_ARG_REQUIRED, "exit", scmd->args[1], t);
		return (2);
	}
	if (scmd->argsc > 2)
	{
		ft_error(E_TOO_MANY_ARGS, "exit", scmd->args[1], t);
		return (2);
	}
	if (ft_checkstr(scmd->args[1], &ft_isdigit) == 0)
	{
		exit_stat = ft_atoi(scmd->args[1]);
		if (exit_stat > 256)
			exit_stat = exit_stat % 16;
	}
	return (exit_stat);
}

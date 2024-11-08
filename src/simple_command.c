#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/redirection.h"

t_scmd	*simple_command(t_token *t)
{
	t_scmd	*s;
	t_scmd	*next_command;

	s = scmd_new();
	while (t)
	{
		if (t->type == ARGUMENT || t->type == COMMAND)
		{
			s->args = ft_arrcat(s->args, t->value, ft_str2dlen(s->args));
			s->argsc ++;
			if (t->type == COMMAND && is_builtin(s->args[0]))
				s->builtin = get_builtin_function(s->args[0]);
		}
		else if (t->type == PIPE)
		{
			next_command = simple_command(t->next);
			s->next = next_command;
			s->pipecount ++;
			if (next_command)
				t->next = NULL;
		}
		else
		{
			set_redirection(s, t);
			t = t->next;
		}
		t = t->next;
	}
	return (s);
}

t_scmd	*scmd_new(void)
{
	t_scmd	*scmd;

	scmd = malloc(sizeof(t_scmd));
	if (!scmd)
		return (NULL);
	scmd->args = NULL;
	scmd->argsc = 0;
	scmd->builtin = NULL;
	scmd->exec_path = NULL;
	scmd->num_redirections = 0;
	scmd->hd_file_name = NULL;
	scmd->redirect_token = NULL;
	scmd->R_INPUT_file = NULL;
	scmd->R_OUTPUT_file = NULL;
	scmd->R_APPEND_file = NULL;
	scmd->redirect_file_name = NULL;
	scmd->old_stdout_fd = 0;
	scmd->old_stdin_fd = 0;
	scmd->new_fd = 0;
	scmd->next = NULL;
	scmd->prev = NULL;
	scmd->pipecount = 0;
	return (scmd);
}

int	(*get_builtin_function(char *command))(t_tools *, t_scmd *)
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
	// else if (!ft_strncmp(command, "exit", len))
	// 	return (&builtinexit);
	else if (!ft_strncmp(command, "history", len))
		return (&builtinhistory);
	return (NULL);
}

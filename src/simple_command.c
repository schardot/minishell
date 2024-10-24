#include "../include/minishell.h"
#include "../include/parser.h"

t_scmd *simple_command(t_token *lst)
{
	t_scmd  *node;
	t_scmd *next_command = NULL;

	node = scmd_new();
	while (lst)
	{
		if (lst->type == ARGUMENT)
			node->args = ft_append_to_array(node->args, lst->value, ft_str2dlen(node->args));
		else if (lst->type == COMMAND)
		{
			node->args = ft_append_to_array(node->args, lst->value, ft_str2dlen(node->args));
			if (is_builtin(lst->value))
				node->builtin = get_builtin_function(lst->value);
		}
		else if (lst->type == REDIRECT_APPEND || lst->type == REDIRECT_OUTPUT || lst->type == REDIRECT_INPUT)
		{
			node->num_redirections++;      // is this important to keep track?
			handle_redirection(node, lst);
		}
		else if (lst->type == PIPE)
		{
			next_command = simple_command(lst->next);
			node->next = next_command;
			if (next_command)
				lst = NULL;
			else
				break ;
		}
		lst = lst->next;
	}
	return (node);
}

void	handle_redirection(t_scmd *node, t_token *lst)
{
	if (lst->type == REDIRECT_APPEND)
	{
		node->redirect_token = ">>";
		node->redirect_append_file = lst->next->value;
	}
	else if (lst->type == REDIRECT_OUTPUT)
	{
		node->redirect_token = ">";
		node->redirect_output_file = lst->next->value;
	}
	else if (lst->type == REDIRECT_INPUT)
	{
		node->redirect_token = "<";
		node->redirect_input_file = lst->next->value;
	}
}

t_scmd *scmd_new(void)
{
	t_scmd *node;

	node = malloc(sizeof(t_scmd));
	if (!node)
		return (NULL);
	node->args = NULL;
	node->builtin = NULL;
	node->num_redirections = 0;
	node->hd_file_name = NULL;
	node->redirect_token = NULL;
	node->redirect_input_file = NULL;
	node->redirect_output_file = NULL;
	node->redirect_append_file = NULL;
	node->redirect_file_name = NULL;
	node->next = NULL;
	node->prev = NULL;
	return (node);
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
	else if (!ft_strncmp(command, "exit", len))
		return (&builtinexit);
	return (NULL);
}
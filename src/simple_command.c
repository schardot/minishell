#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/redirection.h"

t_scmd *simple_command(t_token *lst)
{
	t_scmd *node;
	t_scmd *next_command = NULL;

	node = scmd_new();
	while (lst)
	{
		if (lst->type == ARGUMENT)
			node->args = ft_append_to_arr(node->args, lst->value, ft_str2dlen(node->args));
		else if (lst->type == COMMAND)
		{
			node->args = ft_append_to_arr(node->args, lst->value, ft_str2dlen(node->args));
			if (is_builtin(node->args[0]))
				node->builtin = get_builtin_function(node->args[0]);
		}
		else if (lst->type == REDIRECT_APPEND || lst->type == REDIRECT_OUTPUT || lst->type == REDIRECT_INPUT)
		{
			set_redirection(node, lst);
			// if (handle_redirection(node) < 0)
			// {
			// 	fprintf(stderr, "Error handling redirection for command: %s\n", node->args[0]);
			// 	// Free any allocated resources if necessary
			// 	free(node->args);
			// 	free(node);
			// 	return (NULL); // Return NULL on error
			// }
		}
		else if (lst->type == PIPE)
			{
				next_command = simple_command(lst->next);
				node->next = next_command;
				if (next_command)
					lst->next = NULL;
				else
					break;
			}
		lst = lst->next;
	}
	return (node);
}

char	**ft_append_to_arr(char **arr, char *str, int len)
{
	char	**new;

	new = ft_realloc(arr, (len + 1) * sizeof(char *), \
	(len + 2) * sizeof(char *));
	if (!new)
		return (NULL);
	new[len] = ft_strdup(str);
	if (!new[len])
		return (NULL);
	new[len + 1] = NULL;
	//free (str);
	return (new);
}

t_scmd *scmd_new(void)
{
	t_scmd *node;

	node = malloc(sizeof(t_scmd));
	if (!node)
		return (NULL);
	node->args = NULL;
	node->builtin = NULL;
	node->exec_path = NULL;
	node->quote_token = 0;
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

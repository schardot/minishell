#include "../include/minishell.h"
#include "../include/libft/libft.h"
#include "../include/parser.h"
#include "../include/redirection.h"

int parser(char *input, t_tools *t)
{
	t_scmd		*scmd;
	t_token		*lst;
	t_parser	*parser;

	if (initial_quote_check(input)) //nothing to free here
		return (EXIT_FAILURE);
	parser = init_parser(input); //2 mallocs here
	if (!parser)
		return (EXIT_FAILURE);
	lst = split_arguments(parser, t); //after this function t_parser can be freed
	if (!lst)
		return (EXIT_FAILURE);
	if(syntax_errors(lst, t))
		return (EXIT_FAILURE);
    scmd = simple_command(lst); // after this function t_token can be freed
    if (!scmd)
		return (EXIT_FAILURE);
	check_exec_command(t, scmd); // after this function t_scmd can be freed
    free_structs(scmd, lst, parser);
	return (EXIT_SUCCESS);
}

t_parser	*init_parser(char *input)
{
	t_parser	*new;

	new = malloc(sizeof(t_parser));
	if (!new)
		return (NULL);
	new->input = ft_strdup(input);
	if (!new->input)
    {
        free (new);
        return (NULL);
    }
    new->arg = NULL;
    new->expanded = NULL;
	new->tk_lst = NULL; //does it need to be here?
	return (new);
}

int	syntax_errors(t_token *lst, t_tools *t)
{
	t_token	*tk;

	tk = lst;
	while (tk)
	{
		if (tk->type == PIPE)
		{
			if (!tk->prev || !tk->next)
			{
				ft_fprintf(2, "minishell: syntax error near unexpected token `|'\n");
				return (EXIT_FAILURE);
			}
		}
		else if (tk->type == R_APPEND || tk->type == R_INPUT || tk->type == R_OUTPUT)
		{
			if (!tk->prev  || !tk->next)
			{
				ft_fprintf(2, "minishell: syntax error near unexpected token `newline'\n");
				return (EXIT_FAILURE);
			}
            else if (tk->next->type != ARGUMENT || tk->next->type != COMMAND)
            {
                ft_fprintf(2, "minishell: syntax error near unexpected token `%c'\n", tk->value[0]);
                return (EXIT_FAILURE);
            }
        }
		tk = tk->next;
	}
	return (EXIT_SUCCESS);
}

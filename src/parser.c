#include "../include/minishell.h"
#include "../include/libft/libft.h"
#include "../include/parser.h"
#include "../include/redirection.h"

int parser(char *input, t_tools *t)
{
	t_scmd		*scmd;
	t_token		*lst;
	t_parser	*parser;

	if (initial_quote_check(input))
		return (EXIT_FAILURE);
	parser = init_parser(input);
	if (!parser)
		return (EXIT_FAILURE);
	parser->tokens = split_arguments(parser, t);
	if (!parser->tokens)
		return (EXIT_FAILURE);
	lst = token_list(parser->tokens, t);
	if (!lst)
		return (EXIT_FAILURE);
    scmd = simple_command(lst);
	if (!scmd)
		return (EXIT_FAILURE);
	check_exec_command(t, scmd);
	return (EXIT_SUCCESS);
}

t_parser	*init_parser(char *input)
{
	t_parser	*new;

	new = malloc(sizeof(t_parser));
	if (!new)
		return (NULL);
	new->dq = false;
	new->sq = false;
	new->input = ft_strdup(input);
	if (!new->input)
		return (NULL);
	new->tokens = NULL;
	return (new);
}


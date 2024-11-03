#include "../include/minishell.h"
#include "../include/libft/libft.h"
#include "../include/parser.h"
#include "../include/redirection.h"

char *append_char(char *arg, char c);
char **split_arguments(t_parser *p);
t_parser	*init_parser(char *input);
int check_quote(char c, t_parser *p);
int	initial_quote_check(char *arg);

void parser(char *input, t_tools *t)
{
	char		**tokens;
	t_scmd		*scmd;
	t_token		*lst;
	t_parser	*parser;
	char		**commands;

	if (initial_quote_check(input))
		return ;
	parser = init_parser(input);
	if (!parser)
		return ;
	parser->tokens = split_arguments(parser);
	if (!parser->tokens)
		return ;
	// printf("argumento 0: %s\n", parser->tokens[0]);
	// printf("argumento 1: %s\n", parser->tokens[1]);
	lst = token_list(parser->tokens);
	if (!lst)
		return ;
	scmd = simple_command(lst);
	// printf("argumento: %s\n", scmd->args[0]);
	check_exec_command(t, scmd);
}

t_parser	*init_parser(char *input)
{
	t_parser	*new;

	new = malloc(sizeof(t_parser));
	if (!new)
		return (NULL);
	new->append = false;
	new->dq = false;
	new->sq = false;
	new->input = ft_strdup(input);
	new->quote_token = '\0';
	if (!new->input)
		return (NULL);
	new->tokens = NULL;
	return (new);
}

char **split_arguments(t_parser *p)
{
	int i;
	char *arg;

	i = 0;
	arg = NULL;
	while (p->input[i])
	{
		while (check_quote(p->input[i], p))
			i ++;
		if (p->input[i] && !ft_isspace(p->input[i]) && p->input[i] != '\"' && p->input[i] != '\'')
			p->append = true;
		else if (arg && ft_isspace(p->input[i]) && (!p->sq && !p->dq))
		{
			arg = format_arg(p, arg);
			p->tokens = ft_append_to_array(p->tokens, arg, ft_str2dlen(p->tokens));
			//free(arg);
			p->append = false;
			arg = NULL;
		}
		if(p->append == true)
			arg = append_char(arg, p->input[i]);
		i++;
	}
	arg = trim_quotes(arg);
	if (arg)
	{
		arg = format_arg(p, arg);
		p->tokens = ft_append_to_array(p->tokens, arg, ft_str2dlen(p->tokens));
		//free(arg);
	}
	return (p->tokens);
}

char	*append_char(char *arg, char c)
{
	char	*new_arg;
	int		i;
	int		size;

	i = 0;
	if (!arg)
		size = 2;
	else
		size = ft_strlen(arg) + 2;
	new_arg = malloc(size);
	if (!new_arg)
		return (NULL);
	if (arg)
	{
		ft_strlcpy(new_arg, arg, size);
	}
	new_arg[size - 2] = c;
	new_arg[size - 1] = '\0';
	return (new_arg);
}

char	*format_arg(t_parser *p, char *arg)
{
	initial_quote_check(arg);
	arg = trim_quotes(arg);
	if (arg[0] == '$' && p->quote_token != '\'')
	{
		arg ++;
		arg = getenv(arg);
		if (arg == NULL)
			return (ft_strdup(""));
	}
	return (arg);
}

int	initial_quote_check(char *arg)
{
	bool	dq;
	bool	sq;
	int		i;

	i = 0;
	dq = false;
	sq = false;
	while (arg[i])
	{
		if (arg[i] == '"' && !sq)
			dq = !dq;
		if (arg[i] == '\'' && !dq)
			sq = !sq;
		i ++;
	}
	if (dq || sq)
	{
		ft_putstr_fd("Error: Unclosed quotes in input.\n", 2);
		return (-1);
	}
	return (0);
}
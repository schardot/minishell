#include "../include/minishell.h"
#include "../include/libft/libft.h"
#include "../include/parser.h"
#include "../include/redirection.h"

int	parser(char *input, t_tools *t)
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
	t->exit_status = check_exec_command(t, scmd);
	return (EXIT_SUCCESS);
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
	if (!new->input)
		return (NULL);
	new->quote_token = '\0';
	new->tokens = NULL;
	return (new);
}

char	**split_arguments(t_parser *p, t_tools *t)
{
	int		i;
	char	*arg;

	i = 0;
	arg = NULL;
	while (p->input[i])
	{
		while (check_quote(p->input[i], p))
			i ++;
		if (p->input[i] && !ft_isspace(p->input[i]) && p->input[i] != '\"' \
		&& p->input[i] != '\'')
			p->append = true;
		else if (arg && ft_isspace(p->input[i]) && (!p->sq && !p->dq))
		{
			p = append_token(arg, p, t);
			arg = NULL;
		}
		if (p->append == true)
			arg = append_char(arg, p->input[i]);
		i ++;
	}
	if (arg)
		p = append_token(arg, p, t);
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
		ft_strlcpy(new_arg, arg, size);
	new_arg[size - 2] = c;
	new_arg[size - 1] = '\0';
	return (new_arg);
}

char	*format_arg(t_parser *p, char *arg, t_tools *t)
{
	arg = trim_quotes(arg);
	if (arg[0] == '$')
	{
		if (!arg[1])
			return (arg);
		else if (arg[1] == '?')
			arg = ft_itoa(t->exit_status);
		else if (arg[1] && p->quote_token != '\'')
		{
			arg++;
			arg = ft_getenv(arg, t);
			if (arg == NULL)
				return (ft_strdup(""));
		}
	}
	return (arg);
}

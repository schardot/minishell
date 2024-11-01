#include "../include/minishell.h"
#include "../include/libft/libft.h"
#include "../include/parser.h"
#include "../include/redirection.h"

char *append_char(char *arg, char c);
char **split_arguments(t_parser *p);
t_parser	*init_parser(char *input);
int check_quote(char c, t_parser *p);

void parser(char *input, t_tools *t)
{
	char		**tokens;
	t_scmd		*scmd;
	t_token		*lst;
	t_parser	*parser;

	parser = init_parser(input);
	if (!parser)
		return ;
	parser->tokens = split_arguments(parser);
	if (!parser->tokens)
		return ;
	lst = token_list(parser->tokens);
	if (!lst)
		return ;
	scmd = simple_command(lst);
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
			arg = trim_quotes(arg);
			p->tokens = ft_append_to_arr(p->tokens, arg, ft_str2dlen(p->tokens));
			free(arg);
			p->append = false;
			arg = NULL;
		}
		if(p->append == true)
			arg = append_char(arg, p->input[i]);
		i++;
	}
	arg = trim_quotes(arg);
	if (arg)
		p->tokens = ft_append_to_arr(p->tokens, arg, ft_str2dlen(p->tokens));
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
		free (arg);
	}
	new_arg[ft_strlen(new_arg)] = c;
	new_arg[ft_strlen(new_arg) + 1] = '\0';
	return (new_arg);
}

int	check_quote(char c, t_parser *p)
{
	if (c == '\"' && !p->sq)
	{
		p->dq = !p->dq;
		p->append = !p->append;
		return (1);
	}
	else if (c == '\'' && !p->dq)
	{
		p->sq = !p->sq;
		p->append = !p->append;
		return (1);
	}
	return (0);
}

char	*format_arg(t_scmd *scmd, char *arg)
{
	if (!check_quotes(arg))
			arg = trim_quotes(arg);
	else
		return (NULL);
	if (arg[0] == '$' && scmd->quote_token != '\'')
	{
		arg ++;
		arg = getenv(arg);
		if (arg == NULL)
			return (ft_strdup(""));
	}
	return (arg);
}

int	check_quotes(char *arg)
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
char	*trim_quotes(char *arg)
{
	int	i;
	int	z;

	if (!arg)
		return (NULL);
	z = ft_strlen(arg) - 1;
	i = 0;
	if ((arg[i] == '\'' && arg[z] == '\'') || (arg[i] == '\"' && arg[z] == '\"'))
	{
		// if (arg[i] == '\'' && arg[z] == '\'')
		// 	scmd->quote_token = '\'';
		// else
		// 	scmd->quote_token = '\"';
		arg[z] = '\0';
		arg ++;
	}
	return (arg);
}

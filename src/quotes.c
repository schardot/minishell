#include "../include/minishell.h"
#include "../include/libft/libft.h"
#include "../include/parser.h"
#include "../include/redirection.h"

int	check_quote(char c, t_parser *p)
{
	if (c == '\"' && !p->sq)
	{
		p->dq = !p->dq;
		p->append = true;
		//p->append = !p->append;
		p->quote_token = '\"';
		return (1);
	}
	else if (c == '\'' && !p->dq)
	{
		p->sq = !p->sq;
		p->append = true;
		//p->append = !p->append;
		p->quote_token = '\'';
		return (1);
	}
	return (0);
}

char *trim_quotes(char *arg, bool trim)
{
	int i;
	int z;

	if (!arg)
		return (NULL);
	z = ft_strlen(arg) - 1;
	i = 0;
	if (!ft_strncmp(arg, "\"\"", 2) && trim == false)
		return (arg);
	if ((arg[i] == '\'' && arg[z] == '\'') || (arg[i] == '\"' && arg[z] == '\"'))
	{
		// if (arg[i] == '\'' && arg[z] == '\'')
		// 	scmd->quote_token = '\'';
		// else
		// 	scmd->quote_token = '\"';
		arg[z] = '\0';
		arg++;
	}
	return (arg);
}

int initial_quote_check(char *arg)
{
	bool dq;
	bool sq;
	int i;

	i = 0;
	dq = false;
	sq = false;
	while (arg[i])
	{
		if (arg[i] == '"' && !sq)
			dq = !dq;
		if (arg[i] == '\'' && !dq)
			sq = !sq;
		i++;
	}
	if (dq || sq)
	{
		ft_putstr_fd("Error: Unclosed quotes in input.\n", 2);
		return (-1);
	}
	return (0);
}

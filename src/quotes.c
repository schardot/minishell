#include "../include/minishell.h"
#include "../include/libft/libft.h"
#include "../include/parser.h"
#include "../include/redirection.h"

int	check_quote(char c, char **arg, t_parser *p)
{
	if (c == DQ && !p->sq)
	{
		p->dq = !p->dq;
		return (0);
	}
	else if (c == SQ && !p->dq)
	{
		p->sq = !p->sq;
		return (0);
	}
	return (0);
}

char	*trim_quotes(char *s, bool trim)
{
	int	i;
	int	z;

	if (!s)
		return (NULL);
	z = ft_strlen(s) - 1;
	i = 0;
	if ((s[i] == SQ && s[z] == SQ) || (s[i] == DQ && s[z] == DQ))
	{
		s[z] = '\0';
		s++;
	}
	return (s);
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
		if (arg[i] == DQ && !sq)
			dq = !dq;
		if (arg[i] == SQ && !dq)
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

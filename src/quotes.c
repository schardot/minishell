#include "../include/minishell.h"
#include "../include/libft/libft.h"
#include "../include/parser.h"
#include "../include/redirection.h"

// int check_quote(char *input, int i, char **arg, t_parser *p)
// {
// 	char quote;
// 	char nxt;
// 	char nxtnxt;

// 	quote = input[i];
// 	nxt = input[i + 1];
// 	nxtnxt = input[i + 2];

// 	if (nxt == quote && nxtnxt != ' ' && !ft_strchr(SYMBOL, nxtnxt))
// 		return (i + 2);
// 	if ((quote == DQ && !p->sq) || (quote == SQ && !p->dq))
// 	{
// 		i++;
// 		while (input[i] && input[i] != quote)
// 		{
// 			*arg = append_char(*arg, input[i]);
// 			i++;
// 		}
// 		if (input[i] == quote)
// 		{
// 			if (quote == DQ)
// 				p->dq = !p->dq;
// 			else
// 				p->sq = !p->sq;
// 		}
// 		return (i + 1); // Return index of closing quote
// 	}
// 	return (i + 1);
// }

int check_quote(char c, char **arg, t_parser *p)
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

char	*trim_quotes(char *s)
{
	int	z;
	int	i;

	if (!s)
		return (NULL);
	z = ft_strlen(s) - 1;
	while ((s[0] == SQ && s[z] == SQ) || (s[0] == DQ && s[z] == DQ))
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

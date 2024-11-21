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

//int check_quote(char c, char **arg, t_parser *p)
int	check_quote(char *input, int i, t_parser *p, char **arg, t_tools *t)
{
	char	q;

	q = input[i];
	i++;
	if (q == input[i])
	{
		*arg = ft_strdup("");
		i ++;
		return (i);
	}
	while (input[i] && input[i] != q)
	{
		if (input[i] == '$' && input[i + 1] && q == DQ)
		{
            i ++;
			if (input[i] == '?')
				*arg = ft_itoa(t->exit_status);
			else
			{
				char *expanded = expand_the_argument(input, &i, i, t);  // Expand the variable
				if (*arg)
					*arg = strcat(*arg, expanded);
				else
					*arg = ft_strdup(expanded);
			}
		}
		else
		{
			*arg = append_char(*arg, input[i]);
			if (q == SQ)
				p->sq = true;
			else if (q == DQ)
				p->dq = true;
		}
		i ++;
	}
	if (input[i] == q)

		i ++;
	return (i);
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

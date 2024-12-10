/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:07:49 by ekechedz          #+#    #+#             */
/*   Updated: 2024/12/04 14:07:52 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/libft/libft.h"
#include "../include/parser.h"
#include "../include/redirection.h"

int	check_quote(int i, t_parser *p, t_tools *t)
{
	p->q = p->input[i];
	i ++;
	while (p->input[i] && p->input[i] != p->q)
	{
		if (p->input[i] == '$' && p->input[i + 1] && p->q != '\''
			&& !ft_isspace(p->input[i + 1]) && p->input[i + 1] != p->q)
			i = handle_expansions(p, i, t);
		else
		{
			p->arg = append_char(p->arg, p->input[i]);
			if (p->q == '\'')
				p->sq = true;
			else if (p->q == '"')
				p->dq = true;
			i++;
		}
	}
	if (p->input[i] == p->q)
		i ++;
	return (i);
}

char	*trim_quotes(char *s)
{
	int	z;

	if (!s)
		return (NULL);
	z = ft_strlen(s) - 1;
	while ((s[0] == '\'' && s[z] == '\'') || (s[0] == '"' && s[z] == '"'))
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

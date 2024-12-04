/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:39:41 by nleite-s          #+#    #+#             */
/*   Updated: 2024/12/04 11:39:42 by nleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/libft/libft.h"
#include "../include/parser.h"
#include "../include/redirection.h"

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
	{
		free (arg);
		return (NULL);
	}
	if (arg)
	{
		ft_strlcpy(new_arg, arg, size);
		free (arg);
	}
	new_arg[size - 2] = c;
	new_arg[size - 1] = '\0';
	return (new_arg);
}

char	*expand_the_argument(char *arg, int *i, int st, t_tools *t)
{
	char	*name;
	char	*value;
	int		len;

	len = 0;
	while (arg[st + len] && (ft_isalnum(arg[st + len]) || arg[st + len] == '_'))
		len ++;
	name = ft_substr(arg, st, len);
	if (!name)
		return (NULL);
	value = ft_getenv(name, t);
	free(name);
	if (!value)
		value = ft_strdup("");
	*i += len - 1;
	return (value);
}

static int	process_quote_or_expansion(int i, t_parser *p, t_tools *t)
{
	char	c;

	c = p->input[i];
	if (c == '"' || c == '\'')
		return (check_quote(i, p, t));
	if (c == '$' && p->input[i + 1])
		return (handle_expansions(p, i, t));
	p->arg = append_char(p->arg, c);
	return (i + 1);
}

static int	process_symbol(int i, t_parser *p, t_tools *t, char c)
{
	if (p->arg)
	{
		p = append_token(p, t);
		free(p->arg);
		p->arg = NULL;
	}
	symbol_check(&i, p, t);
	if (ft_isspace(c))
		i++;
	return (i);
}

t_token	*split_arguments(t_parser *p, t_tools *t)
{
	int		i;
	char	c;

	i = 0;
	while (p->input[i])
	{
		c = p->input[i];
		if (c == '"' || c == '\'' || c == '$' || !ft_strchr(SYMBOL, c))
			i = process_quote_or_expansion(i, p, t);
		else
			i = process_symbol(i, p, t, c);
	}
	if (p->arg)
	{
		p = append_token(p, t);
		free(p->arg);
		p->arg = NULL;
	}
	return (p->tk_lst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:24:02 by nataliascha       #+#    #+#             */
/*   Updated: 2024/12/02 17:56:31 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/libft/libft.h"
#include "../include/parser.h"
#include "../include/redirection.h"

int	parser(char *input, t_tools *t)
{
	if (initial_quote_check(input))
		return (t->exit_status);
	t->parser = init_parser(input);
	if (!t->parser)
		return (t->exit_status);
	t->tk = split_arguments(t->parser, t);
	if (!t->tk)
		return (t->exit_status);
	if (syntax_check(t->tk, t))
		return (t->exit_status);
	t->scmd = simple_command(t, t->tk);
	if (!t->scmd)
		return (t->exit_status);
	check_exec_command(t, t->scmd);
	return (t->exit_status);
}

t_parser	*init_parser(char *input)
{
	t_parser	*new;

	new = malloc(sizeof(t_parser));
	if (!new)
		return (NULL);
	new->input = ft_strdup(input);
	if (!new->input)
	{
		free (new);
		return (NULL);
	}
	new->arg = NULL;
	new->expanded = NULL;
	new->tk_lst = NULL;
	new->dq = false;
	new->sq = false;
	new->q = '\0';
	return (new);
}

int	handle_expansions(t_parser *p, int i, t_tools *t)
{
	i++;
	if (p->input[i] == '?')
		p->expanded = ft_itoa(t->exit_status);
	else
		p->expanded = expand_the_argument(p->input, &i, i, t);
	if (p->arg)
		p->arg = ft_strjoin(p->arg, p->expanded);
	else
		p->arg = ft_strdup(p->expanded);
	i++;
	return (i);
}

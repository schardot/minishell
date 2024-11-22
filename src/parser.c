/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nataliaschardosim <nataliaschardosim@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:24:02 by nataliascha       #+#    #+#             */
/*   Updated: 2024/11/22 16:56:18 by nataliascha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	lst = split_arguments(parser, t);
	if (!lst)
		return (EXIT_FAILURE);
	if (syntax_check(lst, t))
		return (EXIT_FAILURE);
	scmd = simple_command(lst);
	if (!scmd)
		return (EXIT_FAILURE);
	check_exec_command(t, scmd);
	free_structs(scmd, lst, parser);
	return (EXIT_SUCCESS);
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
	return (new);
}

int	handle_expansions(t_parser *p, int i, t_tools *t)
{
	i++;
	if (p->input[i] == '?')
		p->arg = ft_itoa(t->exit_status);
	else
	{
		p->expanded = expand_the_argument(p->input, &i, i, t);
		if (p->arg)
			p->arg = ft_strjoin(p->arg, p->expanded);
		else
			p->arg = ft_strdup(p->expanded);
	}
	i++;
	return (i);
}

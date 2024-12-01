/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nataliaschardosim <nataliaschardosim@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:39:49 by nataliascha       #+#    #+#             */
/*   Updated: 2024/12/01 18:50:14 by nataliascha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/libft/libft.h"
#include "../include/parser.h"
#include "../include/redirection.h"

void	free_structs(t_tools *t)
{
	if (t->parser)
		free_parser(t->parser);
	if (t->tk)
		free_token(t->tk);
	if (t->scmd)
		free_scmd(t->scmd);
	if (t->e)
		free (t->e);
	t->parser = NULL;
	t->tk = NULL;
	t->scmd = NULL;
	t->e = NULL;
}

void	free_parser(t_parser *p)
{
	if (p && p->input)
		free (p->input);
	if (p && p->arg)
		free (p->arg);
	free (p);
}

void	free_token(t_token *lst)
{
	t_token	*aux;

	while (lst)
	{
		aux = lst;
		if (lst->value)
			free(lst->value);
		lst = lst->next;
		free (aux);
	}
}

void	free_scmd(t_scmd *s)
{
	t_scmd	*aux;

	while (s)
	{
		aux = s;
		if (s->args)
			ft_free_matrix(s->args);
		if (s->exec_path)
			free (s->exec_path);
		s = s->next;
		free (aux);
	}
}

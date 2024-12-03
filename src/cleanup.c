/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:39:49 by nataliascha       #+#    #+#             */
/*   Updated: 2024/12/03 12:29:10 by nleite-s         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/minishell.h"
#include "../include/libft/libft.h"
#include "../include/parser.h"
#include "../include/redirection.h"

void	free_structs(t_tools *t)
{
	// if (t->parser)
	// 	free_parser(t->parser);
	// if (t->tk)
	// 	free_token(t->tk);
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
	if (p)
	{
		if (p->input)
		{
			free (p->input);
			p->input = NULL;
		}
		if (p && p->arg)
			free (p->arg);
		free_token(p->tk_lst);
		p->tk_lst = NULL;
		// if (p->expanded != NULL)
		// 	free (p->expanded);
		free (p);
		p = NULL;
	}
}

void	free_token(t_token	*lst)
{
	t_token	*aux;

	while (lst)
	{
		aux = lst;
		if (lst->value)
		{
			free(lst->value);
			lst->value = NULL;
		}
		lst = lst->next;
		free (aux);
	}
	lst = NULL;
}

void	free_scmd(t_scmd *s)
{
	t_scmd	*aux;

	while (s)
	{
		aux = s;
		if (aux->args)
		{
			ft_free_matrix(aux->args);
			aux->args = NULL;
		}
		if (aux->exec_path)
		{
			free (aux->exec_path);
			aux->exec_path = NULL;
		}
		s = s->next;
		free (aux);
	}
	s = NULL;
}

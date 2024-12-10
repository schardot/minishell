/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:40:33 by nleite-s          #+#    #+#             */
/*   Updated: 2024/12/04 11:40:33 by nleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/libft/libft.h"
#include "../include/parser.h"
#include "../include/redirection.h"

void	free_structs(t_tools *t)
{
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
	if (p)
	{
		if (p->input)
		{
			free (p->input);
			p->input = NULL;
		}
		if (p && p->arg)
			free (p->arg);
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
		if (aux->value)
		{
			free(aux->value);
			aux->value = NULL;
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
		if (aux->redirect_fd_in != -1)
			close(aux->redirect_fd_in);
		s = s->next;
		free (aux);
	}
	s = NULL;
}

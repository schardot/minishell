/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nataliaschardosim <nataliaschardosim@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:39:49 by nataliascha       #+#    #+#             */
/*   Updated: 2024/11/22 16:39:50 by nataliascha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/libft/libft.h"
#include "../include/parser.h"
#include "../include/redirection.h"

void	free_structs(t_scmd *s, t_token *lst, t_parser *p)
{
	free_parser(p);
	free_token(lst);
	free_scmd(s);
}

void	free_parser(t_parser *p)
{
	if (p->input)
		free (p->input);
	if (p->arg)
		free (p->arg);
	if (p->expanded)
		free (p->expanded);
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

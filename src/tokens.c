/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:36:59 by nataliascha       #+#    #+#             */
/*   Updated: 2024/11/25 14:46:14 by nleite-s         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/minishell.h"
#include "../include/parser.h"

t_token	*tokenlist_new(char *token, t_tools *t, t_parser *p)
{
	t_token	*tk;

	tk = (t_token *)malloc(sizeof(t_token));
	if (tk == NULL)
		return (NULL);
	tk->sq = p->sq;
	tk->dq = p->dq;
	tk->value = ft_strdup(token);
	tk->type = NO_TYPE;
	if (tk->value == NULL)
	{
		free(tk);
		return (NULL);
	}
	tk->prev = NULL;
	tk->next = NULL;
	return (tk);
}

void	tokenlist_addback(t_token **lst, t_token *new)
{
	t_token	*aux;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	aux = *lst;
	while (aux->next)
		aux = aux->next;
	aux->next = new;
	new->prev = aux;
}

void	assign_token_type(t_token *tk, t_tools *t)
{
	int	len;

	if (!tk || !tk->value)
		return ;
	len = ft_strlen(tk->value);
	if (strcmp(tk->value, "|") == 0 && !tk->dq && !tk->sq)
		tk->type = PIPE;
	else if (strcmp(tk->value, ">") == 0 && !tk->dq && !tk->sq)
		tk->type = OUTPUT;
	else if (strcmp(tk->value, "<") == 0 && !tk->dq && !tk->sq)
		tk->type = INPUT;
	else if (strcmp(tk->value, ">>") == 0 && !tk->dq && !tk->sq)
		tk->type = APPEND;
	else if (strcmp(tk->value, "<<") == 0 && !tk->dq && !tk->sq)
		tk->type = R_HEREDOC;
	else if ((tk->prev == NULL || tk->prev->type == PIPE) && \
	(is_builtin(tk->value) || is_executable(tk->value, t)))
		tk->type = COMMAND;
	else
		assign_token_files(tk);
}

void	assign_token_files(t_token *tk)
{
	t_token	*prev;

	// if (!tk->prev)
	// 	tk->type = ARGUMENT;
	if (tk->prev)
		prev = tk->prev;
	if (prev->type == OUTPUT)
		tk->type = O_FILE;
	else if (prev->type == INPUT)
		tk->type = I_FILE;
	else if (prev->type == APPEND)
		tk->type = A_FILE;
	else if (prev->type == R_HEREDOC)
		tk->type = H_DEL;
	if (!tk->type)
		tk->type = ARGUMENT;
}

t_parser	*append_token(t_parser *p, t_tools *t)
{
	t_token	*new;

	new = tokenlist_new(p->arg, t, p);
	if (!p->tk_lst)
		p->tk_lst = new;
	else
		tokenlist_addback(&p->tk_lst, new);
	free (p->arg);
	p->arg = NULL;
	p->sq = false;
	p->dq = false;
	return (p);
}

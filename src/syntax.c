/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:01:03 by nataliascha       #+#    #+#             */
/*   Updated: 2024/12/03 13:58:56 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/libft/libft.h"
#include "../include/parser.h"

static void	syntax_error(char *token);
static int	is_invalid_pipe(t_token *tk);
static int	is_invalid_redirection(t_token *tk);

int	syntax_check(t_token *lst, t_tools *t)
{
	t_token	*tk;

	tk = lst;
	while (tk)
	{
		assign_token_type(tk, t);
		if (tk->type == PIPE)
			t->totalp += 1;
		if (is_invalid_pipe(tk) || is_invalid_redirection(tk))
		{
			t->exit_status = 2;
			return (t->exit_status);
		}
		tk = tk->next;
	}
	return (EXIT_SUCCESS);
}

static int	is_invalid_pipe(t_token *tk)
{
	if (tk->type == PIPE && (!tk->prev || !tk->next))
	{
		syntax_error("|");
		return (1);
	}
	return (0);
}

static int	is_invalid_redirection(t_token *tk)
{
	t_token	*prev;

	if (tk->prev)
		prev = tk->prev;
	if (tk->type == APPEND || tk->type == INPUT
		|| tk->type == OUTPUT || tk->type == R_HEREDOC)
	{
		if (!tk->next)
		{
			syntax_error("newline");
			return (1);
		}
	}
	if (tk->prev && (prev->type == APPEND
			|| prev->type == INPUT || prev->type == OUTPUT))
	{
		if (tk->type != I_FILE && tk->type != O_FILE && tk->type != A_FILE)
		{
			syntax_error(&tk->value[0]);
			return (1);
		}
	}
	return (0);
}

static void	syntax_error(char *token)
{
	ft_fprintf(2, "minishell: syntax error near unexpected token ");
	ft_fprintf(2, "`%s'\n", token);
}

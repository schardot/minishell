/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nataliaschardosim <nataliaschardosim@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:01:03 by nataliascha       #+#    #+#             */
/*   Updated: 2024/11/22 16:39:26 by nataliascha      ###   ########.fr       */
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
		if (is_invalid_pipe(tk) || is_invalid_redirection(tk))
			return (EXIT_FAILURE);
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
	if (tk->type == APPEND || tk->type == INPUT || tk->type == OUTPUT)
	{
		if (!tk->prev || !tk->next)
		{
			syntax_error("newline");
			return (1);
		}
		if (tk->next->type != ARGUMENT && tk->next->type != COMMAND)
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

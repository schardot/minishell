/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:09:02 by nleite-s          #+#    #+#             */
/*   Updated: 2024/12/03 20:09:03 by nleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/redirection.h"

static int	handle_heredoc_redirect(t_tools *t, t_scmd *s, t_token *tk)
{
	if (tk->type == H_DEL)
	{
		s->r_heredoc_delimiter = tk->value;
		if (handle_heredoc_redirection(s) < 0)
		{
			unlink(s->hd_file_name);
			s->heredoc_failed = 1;
			t->exit_status = 1;
			return (1);
		}
	}
	return (0);
}

static t_scmd	*process_pipe_and_command(t_tools *t, t_token *tk, t_scmd *s)
{
	t_scmd	*next_command;

	next_command = NULL;
	if (tk->type == PIPE)
	{
		s->pipetotal++;
		next_command = simple_command(t, tk->next);
		s->next = next_command;
		s->pipecount = s->pipetotal;
		if (next_command)
			tk->next = NULL;
	}
	return (next_command);
}

static int	process_redirection_if_needed(t_tools *t, t_token *tk, t_scmd *s)
{
	if (tk->type != PIPE && tk->type != ARGUMENT && tk->type != COMMAND
		&& tk->type != R_HEREDOC && tk->type != H_DEL && tk->type != NO_TYPE)
	{
		if (!s->skip_exec && process_redirections(t, tk, s) != 0)
		{
			s->skip_exec = 1;
			t->exit_status = 1;
			return (1);
		}
	}
	return (0);
}

t_scmd	*simple_command(t_tools *t, t_token *tk)
{
	t_scmd	*s;
	t_scmd	*next_command;

	s = scmd_new();
	next_command = NULL;
	while (tk)
	{
		if (tk->type == COMMAND && ft_strlen(tk->value) == 0)
		{
			tk->type = NO_TYPE;
			if (!tk->prev && !tk->next)
				return (NULL);
		}
		handle_heredoc_redirect(t, s, tk);
		handle_type(t, tk, s, next_command);
		next_command = process_pipe_and_command(t, tk, s);
		process_redirection_if_needed(t, tk, s);
		tk = tk->next;
	}
	return (s);
}

void	handle_type(t_tools *t, t_token *tk, t_scmd *s, t_scmd *next_command)
{
	char	**new_args;

	if (tk->type == ARGUMENT || tk->type == COMMAND)
	{
		new_args = ft_arrcat(s->args, tk->value, ft_str2dlen(s->args));
		if (!new_args)
		{
			ft_fprintf(2, "Error: Memory allocation failed in ft_arrcat.\n");
			exit ;
		}
		s->args = ft_matrixdup(new_args, ft_str2dlen(new_args));
		ft_free_matrix(new_args);
		s->argsc++;
		if (tk->type == COMMAND && is_builtin(s->args[0]))
			s->builtin = get_builtin_function(s->args[0]);
	}
}

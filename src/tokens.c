#include "../include/minishell.h"
#include "../include/parser.h"

int		token_quotes(char *arg, char quote);
char	*token_value(char *token, bool sq, t_tools *t);
int		syntax_check(t_token *tk, int i, char **tokens);

t_token *token_list(char **tokens, t_tools *t)
{
	int		i;
	t_token	*head;
	t_token	*new;

	i = 0;
	head = tokenlist_new(tokens[i], t);
	if (syntax_check(head, i, tokens))
		return (NULL);
	i ++;
	while (tokens[i])
	{
		new = tokenlist_new(tokens[i], t);
		if (syntax_check(new, i, tokens))
			return (NULL);
		tokenlist_addback(&head, new);
		i++;
	}
	return (head);
}

t_token	*tokenlist_new(char *token, t_tools *t)
{
	t_token	*tk;

	tk = (t_token *)malloc(sizeof(t_token));
	if (tk == NULL)
		return (NULL);
	tk->sq = token_quotes(token, '\'');
	tk->dq = token_quotes(token, '\"');
	tk->value = token_value(token, tk->sq, t);
	if (tk->value == NULL)
	{
		free(tk);
		return (NULL);
	}
	tk->prev = NULL;
	tk->next = NULL;
	tk->redirect_count = 0;
	tk->pipe_count = 0;
	assign_token_type(tk, t);
	return (tk);
}

char *token_value(char *token, bool sq, t_tools *t)
{
	int	i;

	i = 0;
	token = trim_quotes(token, false);
	while (token && token[i])
	{
		if (token[i] == '$' && !sq)
		{
			if (!token[i + 1])
				return (token);
			else if (token[i + 1] == '?')
			{
				token = ft_itoa(t->exit_status);
				if (token == NULL)
					return (NULL);
				if (!ft_strchr(token, '$'))
			   		return (token);
			}
			else if (token[i + 1] && !sq)
			{
				token = expand_the_argument(token, &i, i + 1, t);
				if (token == NULL)
					return (NULL);
				if (!ft_strchr(token, '$'))
			   		return (token);
			}
		}
		i ++;
	}
	return (token);
}

int	token_quotes(char *arg, char quote)
{
	int z;

	if (!arg || ft_strlen(arg) < 2)
		return (0);

	z = ft_strlen(arg) - 1;
	 if (arg[0] == quote && arg[z] == quote)
		return (1);

	return (0);
}

void	tokenlist_addback(t_token **lst, t_token *new)
{
	t_token	*aux;

	if (!new)
		return;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	aux = *lst;
	while (aux->next)
		aux = aux->next;
	aux->next = new;
	aux->prev = aux;
}

void	assign_token_type(t_token *tk, t_tools *t)
{
	int	len;

	if (!tk || !tk->value)
		return;
	len = ft_strlen(tk->value);
	if (ft_strncmp(tk->value, "|", len) == 0 && len == 1 && !tk->dq && !tk->sq)
	{
		tk->type = PIPE;
		tk->pipe_count++;
	}
	else if (ft_strncmp(tk->value, ">", len) == 0 && len == 1 && !tk->dq && !tk->sq)
	{
		tk->type = R_OUTPUT;
		tk->redirect_count++;
	}
	else if (ft_strncmp(tk->value, "<", len) == 0 && len == 1 && !tk->dq && !tk->sq)
	{
		tk->type = R_INPUT;
		tk->redirect_count++;
	}
	else if (ft_strncmp(tk->value, ">>", len) == 0 && len == 2 && !tk->dq && !tk->sq)
	{
		tk->type = R_APPEND;
		tk->redirect_count++;
	}
	else if (ft_strncmp(tk->value, "<<", len) == 0 && len == 2 && !tk->dq && !tk->sq)
	{
		tk->type = R_HEREDOC;
		tk->redirect_count++;
	}
	else if (tk->prev == NULL && (is_builtin(tk->value) || is_executable(tk->value, t)))
		tk->type = COMMAND;
	else
		tk->type = ARGUMENT;
}

t_parser *append_token(char **arg, t_parser *p, t_tools *t)
{
	(void) t;
	if (*arg)
		p->tokens = ft_arrcat(p->tokens, *arg, ft_str2dlen(p->tokens));
	*arg = NULL;
	return (p);
}

int syntax_check(t_token *tk, int i, char **tokens)
{
	if (tk->type == PIPE)
	{
		if (!tokens[i - 1] && !tokens[i + 1])
		{
			ft_fprintf(2, "minishell: syntax error near unexpected token `|'\n");
			return (EXIT_FAILURE);
		}
	}
	else if (tk->type == R_APPEND || tk->type == R_INPUT || tk->type == R_OUTPUT)
	{
		if (!tokens[i - 1] || !tokens[i + 1] || (tokens[i + 1] && tokens[i + 1][0] == '\0'))
		{
            ft_fprintf(2, "minishell: syntax error near unexpected token `newline'\n");
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

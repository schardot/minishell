#include "../include/minishell.h"
#include "../include/parser.h"

t_token	*token_list(char **tokens, t_tools *t)
{
	int		i;
	t_token	*head;
	t_token	*new;

	i = 0;
	head = tokenlist_new(tokens[i], t);
	i ++;
	while (tokens[i])
	{
		new = tokenlist_new(tokens[i], t);
		if(new->redirect_count > 0 &&  !tokens[i + 1])
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return(NULL);
		}
		if(new->pipe_count > 0 &&  !tokens[i + 1])
		{
			printf("minishell: syntax error near unexpected token '|'\n");
			return(NULL);
		}
		tokenlist_addback(&head, new);
		i++;
	}
	return (head);
}

t_token	*tokenlist_new(char *token, t_tools *t)
{
	t_token	*node;

	node = (t_token *)malloc(sizeof(t_token));
	if (node == NULL)
		return (NULL);
	node->value = ft_strdup(token);
	if (node->value == NULL)
	{
		free(node);
		return (NULL);
	}
	node->prev = NULL;
	node->next = NULL;
	node->redirect_count = 0;
	node->pipe_count = 0;
	assign_token_type(node, t);
	// if(!node->next && node->redirect_count)
	// 	return (NULL);
	return (node);
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

void	assign_token_type(t_token *node, t_tools *t)
{
	int	len;

	if (!node || !node->value)
		return;
	len = ft_strlen(node->value);
	if (ft_strncmp(node->value, "|", len) == 0 && len == 1)
	{
		node->type = PIPE;
		node->pipe_count++;
	}
	else if (ft_strncmp(node->value, ">", len) == 0 && len == 1)
	{
		node->type = R_OUTPUT;
		node->redirect_count++;
	}
	else if (ft_strncmp(node->value, "<", len) == 0 && len == 1)
	{
		node->type = R_INPUT;
		node->redirect_count++;
	}
	else if (ft_strncmp(node->value, ">>", len) == 0 && len == 2)
	{
		node->type = R_APPEND;
		node->redirect_count++;
	}
	else if (ft_strncmp(node->value, "<<", len) == 0 && len == 2)
	{
		node->type = R_HEREDOC;
		node->redirect_count++;
	}
	else if (node->prev == NULL && (is_builtin(node->value) || is_executable(node->value, t)))
		node->type = COMMAND;
	else
		node->type = ARGUMENT;
}

t_parser *append_token(char *arg, t_parser *p, t_tools *t)
{
	arg = format_arg(p, arg, t);
	if (arg)
		p->tokens = ft_arrcat(p->tokens, arg, ft_str2dlen(p->tokens));
	p->append = false;
	return (p);
}

#include "../include/minishell.h"
#include "../include/parser.h"

t_token	*token_list(char **tokens)
{
	int		i;
	t_token	*head;
	t_token	*new;

	i = 0;
	head = tokenlist_new(tokens[i]);
	i ++;
	while (tokens[i])
	{
		new = tokenlist_new(tokens[i]);
		tokenlist_addback(&head, new);
		i++;
	}
	return (head);
}

t_token	*tokenlist_new(char *token)
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
	assign_token_type(node);
	return (node);
}

void	tokenlist_addback(t_token **lst, t_token *new)
{
	t_token	*aux;
	t_token	*prev;

	if (!new)
		return;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	aux = *lst;
	while (aux->next)
	{
		// prev = aux;
		aux = aux->next;
	}
	aux->next = new;
	//aux->prev = prev;
	aux->prev = aux; // there is actually for me no change we can talk which one is better implementation
}

void	assign_token_type(t_token *node)
{
	int	len;

	if (!node || !node->value)
		return;
	len = ft_strlen(node->value);
	if (ft_strncmp(node->value, "|", len) == 0 && len == 1)
		node->type = PIPE;
	else if (ft_strncmp(node->value, ">", len) == 0 && len == 1)
		node->type = REDIRECT_OUTPUT;
	else if (ft_strncmp(node->value, "<", len) == 0 && len == 1)
		node->type = REDIRECT_INPUT;
	else if (ft_strncmp(node->value, ">>", len) == 0 && len == 2)
		node->type = REDIRECT_APPEND;
	else if (ft_strncmp(node->value, "<<", len) == 0 && len == 2)
		node->type = HEREDOC;
	else if (node->prev == NULL && (is_builtin(node->value) || is_executable(node->value)))
		node->type = COMMAND;
	else
		node->type = ARGUMENT;
}

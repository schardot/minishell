#include "../include/minishell.h"
#include "../include/parser.h"


//int		syntax_check(t_token *tk, int i, char **tokens);

t_token	*tokenlist_new(char *token, t_tools *t, t_parser *p)
{
	t_token	*tk;

	tk = (t_token *)malloc(sizeof(t_token));
	if (tk == NULL)
		return (NULL);
	tk->sq = p->sq;
	tk->dq = p->dq;
	tk->value = ft_strdup(token);
	if (tk->value == NULL)
	{
		free(tk);
		return (NULL);
	}
	tk->prev = NULL;
	tk->next = NULL;
	//assign_token_type(tk, t);
	return (tk);
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
	new->prev = aux;
}

void	assign_token_type(t_token *tk, t_tools *t)
{
	int	len;

	if (!tk || !tk->value)
		return;
	len = ft_strlen(tk->value);
	if (strcmp(tk->value, "|") == 0 && !tk->dq && !tk->sq)
		tk->type = PIPE;
	else if (strcmp(tk->value, ">") == 0 && !tk->dq && !tk->sq)
		tk->type = R_OUTPUT;
	else if (strcmp(tk->value, "<") == 0 && !tk->dq && !tk->sq)
		tk->type = R_INPUT;
	else if (strcmp(tk->value, ">>") == 0 && !tk->dq && !tk->sq)
		tk->type = R_APPEND;
	else if (strcmp(tk->value, "<<") == 0 && !tk->dq && !tk->sq)
		tk->type = R_HEREDOC;
	else if (tk->prev == NULL && (is_builtin(tk->value) || is_executable(tk->value, t)))
		tk->type = COMMAND;
	else
		assign_token_files(tk);
}

void	assign_token_files(t_token *tk)
{
	t_token *prev;

	if (!tk->prev)
		tk->type = ARGUMENT;
	else if (tk->prev)
		prev = tk->prev;
	if (prev->type == R_OUTPUT)
		tk->type = O_FILE;
	else if (prev->type == R_INPUT)
		tk->type = I_FILE;
	else if (prev->type == R_APPEND)
		tk->type = A_FILE;
	else if (prev->type == R_HEREDOC)
		tk->type = H_DEL;
	if (!tk->type)
		tk->type = ARGUMENT;
}

t_parser *append_token(char **arg, t_parser *p, t_tools *t)
{
	(void) t;
	t_token	*new;

	new = tokenlist_new(*arg, t, p);
	if (!p->tk_lst)
		p->tk_lst = new;
	else
		tokenlist_addback(&p->tk_lst, new);
	//free arg
	*arg = NULL;
	p->sq = false;
	p->dq = false;
	return (p);
}


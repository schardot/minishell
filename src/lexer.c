#include "../include/minishell.h"
#include "../include/libft/libft.h"
#include "../include/parser.h"
#include "../include/redirection.h"

char	*append_char(char *arg, char c)
{
	char	*new_arg;
	int		i;
	int		size;

	i = 0;
	if (!arg)
		size = 2;
	else
		size = ft_strlen(arg) + 2;
	new_arg = malloc(size);
	if (!new_arg)
		return (NULL);
	if (arg)
		ft_strlcpy(new_arg, arg, size);
	new_arg[size - 2] = c;
	new_arg[size - 1] = '\0';
	return (new_arg);
}

char	*expand_the_argument(char *arg, int *i, int st, t_tools *t)
{
	char	*name;
	char	*value;
	char	*new;
	int		len;

	len = 0;
	while (arg[st + len] && (ft_isalnum(arg[st + len]) || arg[st + len] == '_'))
		len ++;
    name = ft_substr(arg, st, len);
	if (!name)
		return (NULL);
	value = ft_getenv(name, t);
    free(name);
    if (!value)
        value = "";
    new = malloc(strlen(arg) + ft_strlen(value) - len);
	if (!new)
		return (NULL);
	strncpy(new, arg, *i);
	strcpy(new + *i, value);
	strcpy(new+ *i + ft_strlen(value), arg + st + len);
	*i += ft_strlen(value) - 1;
	return (new);
}

char	**split_arguments(t_parser *p, t_tools *t)
{
	int		i;
	char	*arg;
	char	c;

	i = 0;
	arg = NULL;
	while (p->input[i])
	{
		c = p->input[i];
		check_quote(c, &arg, p);
		if ((p->sq || p->dq) || !ft_strchr(SYMBOL, c))
			arg = append_char(arg, p->input[i]);
		else
		{
			if (arg)
				p = append_token(&arg, p, t);
			symbol_check(&arg, &i, p, t);
		}
		i ++;
	}
	if (arg)
		p = append_token(&arg, p, t);
	return (p->tokens);
}

void symbol_check(char **arg, int *i, t_parser *p, t_tools *t)
{
	char	c;
	char	*str;
	int	j;

	str = p->input;
	j = *i;
	c = p->input[j];
	if (c == '|' || c == '<' || c == '>')
	{
		*arg = append_char(*arg, str[j]);
        (*i)++;
        if ((c == '<' && str[j + 1] == '<') || (c == '>' && str[j + 1] == '>'))
        {
            *arg = append_char(*arg, str[j]);
            (*i)++;
        }
		p = append_token(arg, p, t);
	}
}

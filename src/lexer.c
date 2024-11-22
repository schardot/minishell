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
	if (!value)
		value = "";
	*i += ft_strlen(name) - 1;
	free(name);
	return (value);
}

t_token	*split_arguments(t_parser *p, t_tools *t)
{
	int		i;
	char	c;

	i = 0;
	while (p->input[i])
	{
		c = p->input[i];
		if (c == DQ || c == SQ)
			i = check_quote(i, p, t);
        else if (c == '$' && p->input[i + 1])
        {
            i ++;
            if (p->input[i] == '?')
                p->arg = ft_itoa(t->exit_status);
            else
            {
                p->expanded = expand_the_argument(p->input, &i, i, t);
                if (p->arg)
                    p->arg = ft_strjoin(p->arg, p->expanded);
                else
                    p->arg = ft_strdup(p->expanded);
            }
            i ++;
		}
		else if (!ft_strchr(SYMBOL, c))
		{
            p->arg = append_char(p->arg, p->input[i]);
            i ++;
		}
		else
		{
            if (p->arg)
                p = append_token(p, t);
            symbol_check(&i, p, t);
            if (ft_isspace(c))
				i++;
		}
	}
    if (p->arg)
        p = append_token(p, t);
    return (p->tk_lst);
}

void symbol_check(int *i, t_parser *p, t_tools *t)
{
	char	c;
	char	*str;
	int	j;

	str = p->input;
	j = *i;
	c = p->input[j];
	if (c == '|' || c == '<' || c == '>')
	{
        p->arg = append_char(p->arg, str[j]);
        (*i)++;
		if ((c == '<' && str[j + 1] == '<') || (c == '>' && str[j + 1] == '>'))
		{
            p->arg = append_char(p->arg, str[j]);
            (*i)++;
		}
        p = append_token(p, t);
    }
}

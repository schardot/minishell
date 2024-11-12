#include "../include/minishell.h"
#include "../include/libft/libft.h"
#include "../include/parser.h"
#include "../include/redirection.h"

char	*expand_the_argument(char *arg, int *i, t_tools *t);

int	parser(char *input, t_tools *t)
{
	t_scmd		*scmd;
	t_token		*lst;
	t_parser	*parser;

	if (initial_quote_check(input))
		return (EXIT_FAILURE);
	parser = init_parser(input);
	if (!parser)
		return (EXIT_FAILURE);
	parser->tokens = split_arguments(parser, t);
	if (!parser->tokens)
		return (EXIT_FAILURE);
	lst = token_list(parser->tokens, t);
	if (!lst)
		return (EXIT_FAILURE);
	scmd = simple_command(lst);
	if (!scmd)
		return (EXIT_FAILURE);

	check_exec_command(t, scmd);
	return (EXIT_SUCCESS);
}

t_parser	*init_parser(char *input)
{
	t_parser	*new;

	new = malloc(sizeof(t_parser));
	if (!new)
		return (NULL);
	new->append = false;
	new->dq = false;
	new->sq = false;
	new->input = ft_strdup(input);
	if (!new->input)
		return (NULL);
	new->quote_token = '\0';
	new->tokens = NULL;
	return (new);
}

#include <stdbool.h>
#include <string.h>

#define SYMBOLS_PARSING " |><"

// Helper function to check if the character is a symbol
static bool is_single_symbol(char c) {
	return strchr(SYMBOLS_PARSING, c) != NULL;
}

// Helper function to check for multi-character symbols (e.g., <<, >>)
static bool is_multi_symbol(const char *input, int i) {
	return (input[i] == '<' && input[i + 1] == '<') || (input[i] == '>' && input[i + 1] == '>');
}

// Helper function to handle quoted content
static int handle_quotes(char *input, int i, char **arg) {
    char quote_char = input[i]; // Store the opening quote type
    *arg = append_char(*arg, input[i]); // Append the opening quote
    i++; // Move past the opening quote

    while (input[i] && input[i] != quote_char) { // Continue until closing quote
        *arg = append_char(*arg, input[i]);
        i++;
    }

    // If we encounter the closing quote, append it and move past it
    if (input[i] == quote_char) {
        *arg = append_char(*arg, input[i]);
        i++;
    }

    return i; // Return the updated index
}

// Handle multi-character symbol (e.g., <<, >>)
static int handle_multi_symbol(char *input, int i, char **arg, t_parser *p, t_tools *t) {
	char symbol[3] = { input[i], input[i + 1], '\0' }; // create symbol string (<< or >>)
	*arg = ft_strdup(symbol); // store the symbol as a token
	p = append_token(*arg, p, t);
	*arg = NULL; // reset arg
	return i + 2; // move index forward by 2
}

char **split_arguments(t_parser *p, t_tools *t) {
	int i = 0;
	char *arg = NULL;

	while (p->input[i])
	{
		if (p->input[i] == '\'' || p->input[i] == '\"') {
			i = handle_quotes(p->input, i, &arg);
			continue;
		}

		// Handle multi-character symbols like << or >>
		if (is_multi_symbol(p->input, i)) {
			if (arg) {
				p = append_token(arg, p, t);
				arg = NULL;
			}
			i = handle_multi_symbol(p->input, i, &arg, p, t);
			continue;
		}

		// Start a new token when encountering non-space, non-symbol characters
		if (!ft_isspace(p->input[i]) && !is_single_symbol(p->input[i])) {
			p->append = true;
		}

		// Append token if end of argument or if encountering single-character symbols or whitespace
		if (arg && (ft_isspace(p->input[i]) || is_single_symbol(p->input[i]))) {
			p = append_token(arg, p, t);
			arg = NULL;
		}

		// Append current character if it's part of a token
		if (p->append) {
			arg = append_char(arg, p->input[i]);
			p->append = false;
		}

		i++;
	}

	// Final append if there's leftover arg
	if (arg) {
		p = append_token(arg, p, t);
	}
	return p->tokens;
}


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

char	*format_arg(t_parser *p, char *arg, t_tools *t)
{
	int	i;
	//arg = trim_quotes(arg, false);

	i = 0;
	while (arg && arg[i])
	{
		if (arg && arg[i] == '$')
		{
			if (!arg[i + 1])
				return (arg);
			else if (arg[i + 1] == '?')
				arg = ft_itoa(t->exit_status);
			else if (arg[i] && p->quote_token != '\'')
			{
				arg = expand_the_argument(arg, &i, t);
			}
		}
		i ++;
	}
	return (arg);
}

#include <stdlib.h>
#include <string.h>

char	*expand_the_argument(char *arg, int *i, t_tools *t)
{
	char	*var_name;
	char	*var_value;
	char	*new_arg;
	int		start = *i + 1;
	int		len = 0;

	while (arg[start + len] && (ft_isalnum(arg[start + len]) || arg[start + len] == '_'))
		len++;
	var_name = ft_substr(arg, start, len);
	if (!var_name)
		return (NULL);
	var_value = ft_getenv(var_name, t);
	if (!var_value)
		return (NULL);
	new_arg = malloc(strlen(arg) + strlen(var_value) - len);
	if (!new_arg)
		return (NULL);
	strncpy(new_arg, arg, *i);
	strcpy(new_arg + *i, var_value);
	strcpy(new_arg + *i + strlen(var_value), arg + start + len);
	*i += strlen(var_value) - 1;
	return (new_arg);
}

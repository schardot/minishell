#include "../include/minishell.h"
#include "../include/libft/libft.h"
#include "../include/parser.h"
#include "../include/redirection.h"

void	parser(char *input, t_tools *t)
{
	char	**tokens;
	t_scmd	*scmd;
	t_token	*lst;

	check_quotes(input);
	tokens = ft_split(input, ' ');
	if (!tokens)
		return ;
	lst = token_list(tokens);
	if (!lst)
		return ;
	scmd = simple_command(lst);
	check_exec_command(t, scmd);
}

char	*format_arg(t_scmd *scmd, char *arg)
{
	if (!check_quotes(arg))
			arg = trim_quotes(arg, scmd);
	else
		return (NULL);
	if (arg[0] == '$' && scmd->quote_token != '\'')
	{
		arg ++;
		arg = getenv(arg);
		if (arg == NULL)
			return (ft_strdup(""));
	}
	return (arg);
}

int	check_quotes(char *arg)
{
	bool	dq;
	bool	sq;
	int		i;

	i = 0;
	dq = false;
	sq = false;
	while (arg[i])
	{
		if (arg[i] == '"' && !sq)
			dq = !dq;
		if (arg[i] == '\'' && !dq)
			sq = !sq;
		i ++;
	}
	if (dq || sq)
	{
		ft_putstr_fd("Error: Unclosed quotes in input.\n", 2);
		return (-1);
	}
	return (0);
}

char	*trim_quotes(char *arg, t_scmd *scmd)
{
	int	i;
	int	z;

	z = ft_strlen(arg) - 1;
	i = 0;
	if ((arg[i] == '\'' && arg[z] == '\'') || (arg[i] == '\"' && arg[z] == '\"'))
	{
		if (arg[i] == '\'' && arg[z] == '\'')
			scmd->quote_token = '\'';
		else
			scmd->quote_token = '\"';
		arg[z] = '\0';
		arg ++;
	}
	return (arg);
}

#include "../include/minishell.h"
#include "../include/libft/libft.h"
#include "../include/parser.h"

void	parser(char *input, t_tools *t)
{
	char	**tokens;
	t_scmd	*scmd;
	t_token	*lst;

	tokens = split_tokens(input);
	if (!tokens)
		return ;
	lst = token_list(tokens);
	if (!lst)
		return ;
	scmd = simple_command(lst);
	check_exec_command(t, scmd);
}

char    **split_tokens(char *input)
{
    bool    dq;
    bool    sq;
    int     i;

    dq = false;
    sq = false;
    i = 0;
    while (input[i])
    {
		if (input[i] == '"' && !sq)
			dq = !dq;
		if (input[i] == '\'' && !dq)
			sq = !sq;
        if ((dq && sq) || (dq && !sq) || (!dq && sq))
            add_to_argument
		i ++;
    }
}

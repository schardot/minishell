#include "../include/minishell.h"

int	lexer(char *input) //this is the main function for this part of the parsing
{
	char **tokens;

	if (check_quotes(input) != 0)
		return (NULL);
	tokens = ft_split(input, ' ');
	return (tokens);
}

// Function that checks if a quote was left open (double or single). According to chatgpt, the ONLY THING that would make me stop executing the process during the tokenization part is if i find open quotes. The others erros arent fatal and are catched later.
int check_quotes(char *input)
{
	bool dq;
	bool sq; // they have to be bool so i can perform an operation like a light on and off.
	int i;

	i = 0;
	dq = false;
	sq = false;
	while (input[i])
	{
		if (input[i] == '"' && !sq) // if we find a double quote and we are not inside a single quote : ex: echo "a is incorrect, but echo '"a' will print "a
			dq = !dq;
		if (input[i] == '\'' && !dq) // same thing as before but opposite
			sq = !sq;
		i++;
	}
	if (dq || sq)
	{
		ft_putstr_fd("Error: Unclosed quotes in input.\n", 2);
		free (input);
		return (-1);
	}
	return (0);
}


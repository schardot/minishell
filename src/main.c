#include "../include/minishell.h"
#include "../include/libft/get_next_line/get_next_line.h"

int main(int argc, char **argv, char **envp)
{
	char	*input;
	char	**tokens;

	if (argc != 1)
	{
		printf("No arguments necessary");
		exit (0);
	}
	while (1)
	{
		input = getinput();
		tokens = lexer(input);
		parser(tokens);
	}
	return (0);
}

char *get_input(void)
{
	char *input;

	input = readline("\033[1;36mminishell\033[95m$ \033[0m");
	if (input && *input)
		add_history(input);
	return (input);
}
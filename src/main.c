#include "../include/minishell.h"

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
		if (input)
			parser(input);
	}
	return (0);
}

char *get_input(void)
{
	char *input;

	input = readline("\033[1;36mminishell\033[95m$ \033[0m");
	if (input == NULL) // Handle Ctrl+D (EOF)
		printf("\nExiting shell...\n");
	if (*input)
		add_history(input);
	return (input);
}

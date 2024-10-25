#include "../include/minishell.h"
#include "../include/parser.h"

int main(int argc, char **argv, char **envp)
{
	char	*input;
	t_tools *t;

	t = init_t_tools(envp);
	(void)argv;
	(void)argc;
	if (argc != 1)
	{
		printf("No arguments necessary");
		exit (0);
	}
	while (1)
	{
		input = get_input();
		if (input)
			parser(input, t);
	}
	return (0);
}

char *get_input(void)
{
	char *input;

	input = readline("\033[1;36mminishell\033[95m$ \033[0m");
	if (input == NULL) // Handle Ctrl+D (EOF)
		printf("\nExiting shell...\n");
	if (input)
		add_history(input);
	return (input);
}

t_tools	*init_t_tools(char **envp)
{
	t_tools *node;

	node = malloc(sizeof(t_tools));
	if (!node)
		return (NULL);
	node->envp = envp;
	//maybe this struct is going to have more stuff, if not i will destroy it
	return (node);
}
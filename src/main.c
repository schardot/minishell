#include "../include/minishell.h"
#include "../include/parser.h"

struct sigaction	sa;

int main(int argc, char **argv, char **envp)
{
	char	*input;
	t_tools *t;

	if (argc != 1)
	{
		printf("No arguments necessary");
		exit (0);
	}
	t = init_t_tools(envp);
	if (!t)
	{
		fprintf(stderr, "Failed to initialize tools\n");
		return (EXIT_FAILURE);
	}
	setup_signal_handling();
	while (1)
	{
		input = get_input();
		if (input)
			parser(input, t);
		if (!input)				   // Handle EOF (Ctrl+D)
			break;
		free(input);
	}
	free(t);
	return (0);
}

char *get_input(void)
{
	char *input;

	input = readline("\033[1;36mminishell\033[95m$ \033[0m");
	if (input == NULL) // Handle Ctrl+D (EOF)
		return (NULL);
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

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	setup_signal_handling(void)
{
	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(1);
	}
	signal(SIGQUIT, SIG_IGN);
}
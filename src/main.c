#include "../include/minishell.h"
#include "../include/parser.h"

int	main(int argc, char **argv, char **envp)
{
	//char				*input;
	(void)**argv;
	t_tools				*t;
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	if (argc != 1)
	{
		printf("No arguments necessary");
		return (EXIT_FAILURE);
	}
	t = init_t_tools(envp);
	if (!t)
	{
		ft_putstr_fd("Failed to initialize tools\n", 2);
		return (EXIT_FAILURE);
	}
	setup_signal_handling(&sa_int, &sa_quit);
	while (1)
	{
		if (get_input(t, &sa_int, &sa_quit) == EXIT_FAILURE)
			break ;
	}
	free(t);
	clear_history();
	return (t->exit_status);
}

int get_input(t_tools *t, struct sigaction *sa_int, struct sigaction *sa_quit)
{
	char	*input;

	input = readline("\033[1;36mminishell\033[95m$ \033[0m");
	if (!input)
	{
		printf("exit\n");
		return (EXIT_FAILURE);
	}
	if (input[0] != '\0')
	{
		add_history(input);
		parser(input, t);
	}
	printf("Received input: %s\n", input);
	free (input);
	return (EXIT_SUCCESS);
}

t_tools	*init_t_tools(char **envp)
{
	t_tools	*n_tools;

	n_tools = malloc(sizeof(t_tools));
	if (!n_tools)
		return (NULL);
	n_tools->envp = ft_matrixdup(envp, ft_str2dlen(envp));
	if (!n_tools->envp)
		return (NULL);
	n_tools->pipefd[0] = -1;
	n_tools->pipefd[1] = -1;

	n_tools->exit_status = 0;
	return (n_tools);
}

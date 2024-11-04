#include "../include/minishell.h"
#include "../include/parser.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_tools	*t;

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
	setup_signal_handling();
	while (1)
	{
		if (get_input(t) == EXIT_FAILURE)
			break ;
	}
	free(t); //actually we need a cleanup function
	return (0);
}

int	get_input(t_tools *t)
{
	char	*input;

	input = readline("\033[1;36mminishell\033[95m$ \033[0m");
	if (!input)
	{
		printf("\n");
		return (EXIT_FAILURE);
	}
	if (input[0] != '\0')
	{
		add_history(input);
		parser(input, t);
	}
	free (input);
	return (EXIT_SUCCESS);
}

t_tools	*init_t_tools(char **envp)
{
	t_tools	*n_tools;
	int		i;

	n_tools = malloc(sizeof(t_tools));
	if (!n_tools)
		return (NULL);
	n_tools->envp = ft_matrixdup(envp, ft_str2dlen(envp));
	if (!n_tools->envp)
		return (NULL);
	return (n_tools);
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

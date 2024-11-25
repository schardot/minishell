/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:58:50 by nataliascha       #+#    #+#             */
/*   Updated: 2024/11/25 09:46:19 by nleite-s         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../include/minishell.h"
#include "../include/parser.h"

int	free_tools(t_tools *t);

int	main(int argc, char **argv, char **envp)
{
	t_tools				*t;
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	int					exit;

	if (argc != 1 || argv[1])
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
	exit = free_tools(t);
	clear_history();
	return (exit);
}

int	get_input(t_tools *t, struct sigaction *sa_int, struct sigaction *sa_quit)
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
	free (input);
	return (EXIT_SUCCESS);
}

t_tools	*init_t_tools(char **envp)
{
	t_tools	*t;

	t = malloc(sizeof(t_tools));
	if (!t)
		return (NULL);
	t->envp = ft_matrixdup(envp, ft_str2dlen(envp));
	if (!t->envp)
	{
		free (t);
		return (NULL);
	}
	t->pipefd[0] = -1;
	t->pipefd[1] = -1;
	t->exit_status = 0;
	return (t);
}

int	free_tools(t_tools *t)
{
	int	exit;

	exit = t->exit_status;
	ft_free_matrix(t->envp);
	free(t);
	return (exit);
}

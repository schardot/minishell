/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:09:06 by ekechedz          #+#    #+#             */
/*   Updated: 2024/12/04 14:09:08 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/parser.h"

int		free_tools(t_tools *t);
void	reset_structs(t_tools *t);

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
		return (EXIT_FAILURE);
	setup_sig_hand(&sa_int, &sa_quit);
	while (t->exit == 0)
	{
		reset_structs(t);
		if (get_input(t, &sa_int, &sa_quit) == EXIT_FAILURE)
			break ;
		free_structs(t);
	}
	exit = free_tools(t);
	rl_clear_history();
	return (exit);
}

void	reset_structs(t_tools *t)
{
	t->totalp = 0;
	if (t->parser)
	{
		t->parser->sq = false;
		t->parser->dq = false;
	}
}

int	get_input(t_tools *t, struct sigaction *sa_int, struct sigaction *sa_quit)
{
	char	*input;

	(void)sa_int;
	(void)sa_quit;
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
	free(input);
	free_structs(t);
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
		free(t);
		return (NULL);
	}
	t->pipefd[0] = -1;
	t->pipefd[1] = -1;
	t->exit_status = 0;
	t->exit = 0;
	t->parser = NULL;
	t->tk = NULL;
	t->scmd = NULL;
	t->e = NULL;
	t->totalp = 0;
	return (t);
}

int	free_tools(t_tools *t)
{
	int	exit;

	exit = t->exit_status;
	free_structs(t);
	ft_free_matrix(t->envp);
	free(t);
	return (exit);
}

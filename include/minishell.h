#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "parser.h"
# include <stdio.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>

#define MAX_INPUT_SIZE 1024

int     get_input(t_tools *t);
t_tools *init_t_tools(char **envp);
void	handle_signal(int sig);
void	setup_signal_handling(void);

#endif
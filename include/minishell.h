#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>

# include "libft/libft.h"
# include "parser.h"
# include <readline/readline.h>
# include <readline/history.h>

#define MAX_INPUT_SIZE 1024

static int interupted_flag = 0;

int     get_input(t_tools *t);
t_tools *init_t_tools(char **envp);
void	handle_signal(int sig);
void	setup_signal_handling(void);

#endif

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



int	get_input(t_tools *t, struct sigaction *sa_int, struct sigaction *sa_quit);
t_tools *init_t_tools(char **envp);
void default_sigint_handler(int signum);
void setup_signal_handling(struct sigaction *sa_int, struct sigaction *sa_quit);
void switch_signal_handlers(struct sigaction *sa_int, struct sigaction *sa_quit, bool pr);

#endif

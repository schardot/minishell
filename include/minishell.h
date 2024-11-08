#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
#include <unistd.h>
 #include <errno.h>
# include "libft/libft.h"
# include "parser.h"
# include <readline/readline.h>
# include <readline/history.h>

#define MAX_INPUT_SIZE 1024

typedef enum
{
    E_NO_SUCH_FILE,
    E_NOT_A_DIR,
    E_PERMISSION_DENIED,
    E_NOT_A_VALID_ID,
    E_NUM_ARG_REQUIRED,
    E_TOO_MANY_ARGS,
    E_COMMAND_NOT_FOUND,
    E_UNKNOWN_ERROR // Optional: for catching unhandled errors
} t_error;

int	get_input(t_tools *t, struct sigaction *sa_int, struct sigaction *sa_quit);
t_tools *init_t_tools(char **envp);
void default_sigint_handler(int signum);
void setup_signal_handling(struct sigaction *sa_int, struct sigaction *sa_quit);
void switch_signal_handlers(struct sigaction *sa_int, struct sigaction *sa_quit, bool pr);

void ft_error(t_error type, char *cmd, char *inv_arg, t_tools *t);
#endif

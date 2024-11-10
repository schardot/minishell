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

# define MAX_INPUT_SIZE 1024
# define MINI "minishell"

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

static int interupted_flag = 0;

int get_input(t_tools *t, struct sigaction *sa_int, struct sigaction *sa_quit);
t_tools *init_t_tools(char **envp);
void default_sigint_handler(int signum);
void setup_signal_handling(struct sigaction *sa_int, struct sigaction *sa_quit);
void switch_signal_handlers(struct sigaction *sa_int, struct sigaction *sa_quit, bool pr);

void ft_error(t_error type, char *cmd, char *inv_arg, t_tools *t);

#endif

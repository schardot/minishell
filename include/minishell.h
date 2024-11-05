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
    E_UNKNOWN_ERROR // Optional: for catching unhandled errors
} t_error;

struct sigaction sa;

int     get_input(t_tools *t);
t_tools *init_t_tools(char **envp);
void	handle_signal(int sig);
void	setup_signal_handling(void);

void ft_error(t_error type, char *cmd, t_scmd *scmd);

#endif
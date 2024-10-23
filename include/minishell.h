#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "stdio.h"
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <errno.h>
# include <string.h>

#define MAX_INPUT_SIZE 1024

char    *get_input(void);

#endif
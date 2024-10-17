#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "stdio.h"
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

#define MAX_INPUT_SIZE 1024

int     check_quotes(char *input);
char    *get_input(void);

#endif
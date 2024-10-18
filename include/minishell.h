#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "stdio.h"
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <errno.h>

typedef struct s_scmd { //struct for simplecommands, not using it yet
    char    *cmd;
    char    *args;
	t_scmd	*next;
} t_scmd;

#define MAX_INPUT_SIZE 1024

int     check_quotes(char *input);
char    *get_input(void);

#endif
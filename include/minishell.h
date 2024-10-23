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

typedef struct s_scmd { //struct for simplecommands, not using it yet
    char			**tokens;
	struct s_scmd	*next;
}	t_scmd;

#define MAX_INPUT_SIZE 1024

char    *get_input(void);
void	parser(char *input);
void	check_exec_command(char **command);
int		is_builtin(char *token);
int		is_executable(char *cmd);
int		is_executable(char *cmd);
void    execute_builtin(char **cmd, int len);
void	cd(const char *path);
void	pwd(void);

#endif
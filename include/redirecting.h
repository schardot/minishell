#ifndef REDIRECTION_H
# define REDIRECTION_H

# include <unistd.h>  // For file descriptors, dup2, close
# include <fcntl.h>   // For open(), O_CREAT, O_WRONLY, etc.
# include "minishell.h"
# include "parser.h"

# define INPUT_REDIRECT  1   // Redirect input: <
# define OUTPUT_REDIRECT 2   // Redirect output: >
# define APPEND_REDIRECT 3   // Append output: >>
# define HEREDOC_REDIRECT 4  // Heredoc: <<

// Struct to manage file descriptors during redirection
typedef struct	s_redirection
{
	int	input_fd;
	int	output_fd;
}	t_redirection;

int handle_redirection(t_scmd *scmd);
int setup_input_redirection(char *file_name);
int setup_output_redirection(char *file_name, int append);
void restore_stdio(int saved_stdin, int saved_stdout);
int setup_heredoc(char *delimiter);

#endif

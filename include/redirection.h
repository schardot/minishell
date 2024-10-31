#ifndef REDIRECTION_H
# define REDIRECTION_H

# include <unistd.h>   // For dup2, close
# include <fcntl.h>    // For open, O_CREAT, O_WRONLY, etc.
# include "../include/parser.h"  // Adjust path as necessary to access t_scmd definition
# include "../include/minishell.h"
// Define modes for redirection
# define INPUT_REDIRECT   1   // Redirect input: <
# define OUTPUT_REDIRECT  2   // Redirect output: >
# define APPEND_REDIRECT  3   // Append output: >>
# define HEREDOC_REDIRECT 4   // Heredoc: <<

// Struct to manage file descriptors during redirection
typedef struct s_redirection
{
	int input_fd;
	int output_fd;
} t_redirection;

// Function prototypes for redirection handling
int handle_redirection(t_scmd *node); // Uses t_scmd struct
int setup_input_redirection(char *file_name);
int setup_output_redirection(char *file_name, int append);
int setup_heredoc(char *delimiter); // Optional, for heredoc implementation
void restore_stdio(int saved_stdin, int saved_stdout);


void	set_redirection(t_scmd *node, t_token *lst);
void	restore_stdout(t_scmd *node);
int		handle_append_redirection(t_scmd *node);
int 	handle_output_redirection(t_scmd *node);
int		handle_input_redirection(t_scmd *node);
void	set_redirection(t_scmd *node, t_token *lst);

#endif

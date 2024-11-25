#ifndef REDIRECTION_H
# define REDIRECTION_H

# include <unistd.h>   // For dup2, close
# include <fcntl.h>    // For open, O_CREAT, O_WRONLY, etc.
# include "../include/parser.h"  // Adjust path as necessary to access t_scmd definition
# include "../include/minishell.h"

typedef struct s_redirection
{
	int input_fd;
	int output_fd;
} t_redirection;

// Function prototypes for redirection handling
int	handle_redirection(t_scmd *node); // Uses t_scmd struct

// Function prototypes for pipe handling
int create_pipe_if_needed(t_tools *t, int has_next, t_scmd *scmd);
// In redirection.h
void execute_child_process(t_tools *t, t_scmd *scmd, int prev_fd, int has_next);
void close_unused_pipes(int *prev_fd, t_tools *t, int has_next);
void setup_pipe_for_child(int prev_fd, t_tools *t, int has_next);
void finalize_parent_process(int *prev_fd, t_tools *t, int has_next);

// Function prototypes for redirection handling
void set_redirection(t_scmd *node, t_token *lst);
void	restore_stdout(t_scmd *node);

int     handle_HEREDOC_redirection(t_scmd *node);

int wait_for_pids(pid_t *pids, int count, t_tools *t);
void	sigquit_handler(int signum);
void	switch_signal_handlers(struct sigaction *sa_int, struct sigaction *sa_quit, bool pr_int, bool pr_quit);
#endif

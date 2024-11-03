#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/redirection.h"

// Create a pipe if the current command has a next command
int create_pipe_if_needed(t_tools *t, int has_next)
{
    if (has_next)
    {
        if (pipe(t->pipefd) == -1)
        {
            perror("pipe");
            return -1;
        }
    }
    return 0;
}

// Set up the pipe for the child process:
// - If there's a previous command, read from prev_fd.
// - If there's a next command, write to pipefd[1].
void setup_pipe_for_child(int prev_fd, t_tools *t, int has_next)
{
    if (prev_fd != -1)
    {
        dup2(prev_fd, STDIN_FILENO);
        close(prev_fd);
    }
    if (has_next)
    {
        close(t->pipefd[0]); // Close read-end in the child
        dup2(t->pipefd[1], STDOUT_FILENO);
        close(t->pipefd[1]);
    }
}

// Close the unused pipe ends in the parent process
void close_unused_pipes(int *prev_fd, t_tools *t, int has_next)
{
    if (*prev_fd != -1)
    {
        close(*prev_fd); // Close previous read-end
    }
    if (has_next)
    {
        close(t->pipefd[1]);     // Close write-end in the parent
        *prev_fd = t->pipefd[0]; // Update prev_fd to new read-end for the next command
    }
    else
    {
        *prev_fd = -1;
    }
}

void execute_child_process(t_tools *t, t_scmd *scmd, int prev_fd, int has_next)
{
    setup_pipe_for_child(prev_fd, t, has_next);

    if (is_builtin(scmd->args[0]))
    {
        scmd->builtin(t, scmd);
        exit(0);
    }
    else if (is_executable(scmd->args[0]))
    {
        scmd->exec_path = is_executable(scmd->args[0]);
        execve(scmd->exec_path, scmd->args, t->envp);
        perror("execve");
        exit(1);
    }
    else
    {
        printf("minishell: command not found: %s\n", scmd->args[0]);
        exit(127);
    }
}

void finalize_parent_process(int *prev_fd, t_tools *t, int has_next)
{
    // Close unused pipe ends in the parent process
    close_unused_pipes(prev_fd, t, has_next);

    // Wait for all child processes to complete
    int status;
    while (wait(&status) > 0)
        ;
}
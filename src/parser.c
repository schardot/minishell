#include "../include/minishell.h"

void    parser(char **tokens)
{
    /* Overview of parser
Input Parameters:

char **tokens: An array of strings (tokens) that represent the input command split by whitespace and other delimiters.
int token_count: (Optional) The total number of tokens to help manage iterations if necessary.
Purpose:

Convert the flat list of tokens into a structured format (e.g., an array of simplecommand structs).
Handle special cases such as pipes (|), input/output redirections (<, >, >>, <<).
Manage command grouping and ensure that each command is correctly associated with its arguments.
Expected Flow:

Initialization: Start by initializing necessary structures, such as an array of simplecommand pointers and counters for the number of commands and arguments.
Iterate through Tokens: Loop through the token array:
Identify Commands: When encountering a token that represents a command, create a new simplecommand struct and store the command name.
Store Arguments: For subsequent tokens that are not commands or operators, treat them as arguments for the last added command.
Handle Pipes: When encountering a pipe (|), finalize the current command and prepare to start a new command.
Handle Redirections: Identify tokens that represent redirection operators and link them to the appropriate commands.
Finalization: After processing all tokens, ensure any remaining commands are finalized and stored.
Return Value:

The function may return a dynamically allocated array of simplecommand pointers and the count of commands. Alternatively, it can modify pointers passed in as parameters for the commands and counts.
Error Handling:

Handle any errors such as memory allocation failures, unmatched quotes, or incorrect syntax gracefully. */
}

//This doesnt work for the long run, im just keeping it here so i can remember how execve works
int parse_input(char *input, int len)
{
    char *args[] = {NULL, NULL};
    int pid;

    if (ft_strncmp(input, "exit", len) == 0)
    {
        free(input);
        return (1);
    }
    if (ft_strncmp(input, "ls", len) == 0)
    {
        pid = fork();
        if (pid == 0)
        {
            args[0] = ft_strdup("/bin/ls");
            execve("/bin/ls", args, NULL);
            perror("execve");
            exit(1);
        }
        else if (pid > 0)
            wait(NULL);
        else
            perror("fork failed");
        free(input);
        return (0);
    }
}
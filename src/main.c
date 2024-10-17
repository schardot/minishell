#include "../include/minishell.h"
#include "../include/libft/get_next_line/get_next_line.h"

int main(int argc, char **argv)
{
	char	*input;
	int		len;
	char	*args[] = {NULL, NULL}; // Array for execve arguments

	pid_t	pid;

	if (argc != 1)
	{
		printf("No arguments necessary");
		exit (0);
	}
	while (1)
	{
		input = readline("\033[1;36mminishell\033[95m$ \033[0m"); //this is an allowed external function that prints what we pass to it and acts line get_next_line(0)
		len = ft_strlen(input);
		if (len > 0 && input[len - 1] == '\n') //we have to take out the newline
			input[ft_strlen(input) - 1] = '\0';
		add_history(input); //adds the input to the history, its also an allowed external function
		if (ft_strncmp(input, "exit", len) == 0)
		{
			free (input);
			break;
		}
		if (ft_strncmp(input, "ls", len) == 0) //im just trying to implement ls and understand how execve works
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
			free (input);
		}
	}
	return (0);
}
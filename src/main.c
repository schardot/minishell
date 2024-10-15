#include "../include/minishell.h"
#include "../include/libft/get_next_line/get_next_line.h"

int main(int argc, char **argv)
{
	char	input[MAX_INPUT_SIZE];
	char	*line;
	int		len;
	char	*args;
	pid_t	pid;

	if (argc != 1)
	{
		printf("No arguments necessary");
		exit (0);
	}
	while (1)
	{
		printf("\033[1;36mminishell\033[95m$ \033[0m");
		line = get_next_line(0);
		len = ft_strlen(line);
		// if (line)
		// 	add_to_history(); ---------------- implement
		line[ft_strlen(line) - 1] = '\0';
		if (ft_strncmp(line, "exit", len) == 0)
		{
			free (line);
			break;
		}
		if (ft_strncmp(line, "ls", len) == 0)
		{
			pid = fork();
			if (pid == 0)
			{
				args = ft_strdup("/bin/ls, NULL");
				execve("/bin/ls", &args, NULL);
			}
			else if (pid > 0)
                wait(NULL);
			else
                perror("fork failed");
			free (line);
		}
	}
	return (0);
}
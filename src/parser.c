#include "../include/minishell.h"
#include "../include/libft/libft.h"

void	parser(char *input) //im just trying to deal with "ls -a | wc -l"
{
	char	**cmmnds;
	char	**tokens;
	int		i;

	i = 0;
	cmmnds = ft_split(input, '|');
	while (cmmnds[i])
	{
		tokens = ft_split(cmmnds[i], ' ');
		check_exec_command(tokens);
		free (tokens);
	}
	//free (cmmnds)? not sure
}

//lets say we passed ls -l | wc -l. before passing to this function, we have to separate "ls, -l" and "wc, -l".
void    check_exec_command(char **command)
{
	int pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (is_builtin(command[0]))
		{
			// execute_builtin() it but we have to write those functions yet
			exit (0);
		}
		if (is_executable(command[0]))
		{
			execve(command[0], command, NULL);
			perror("execve");
			exit(1);
		}
		else
		{
			printf("%s: command not found", command[0]);
			exit(127); // exit with command not found status
		}
	}
	else if (pid < 0)
		perror("fork");
	else
		waitpid(pid, &status, 0);
	ft_free_matrix(command);
}

int is_builtin(char *token)
{
	int len;

	len = ft_strlen(token);
	if (!ft_strncmp(token, "cd", len) || !ft_strncmp(token, "pwd", len) || !ft_strncmp(token, "echo", len) || ft_strncmp(token, "exit", len))
		return (1); // it's a built-in
	return(0); // not a built-in
}

int is_executable(char *cmd)
{
	char    *path_env;
	char    **paths;
	char    full_path[1024];
	int     i;

	i = 0;
	path_env = getenv("PATH");
	if (path_env == NULL)
		return 0; // PATH not set, command can't be found
	paths = ft_split(path_env, ':');
	if (paths == NULL)
		return 0; // Failed to split PATH, exit early
	while (paths[i])
	{
		full_path[0] = '\0';
		ft_strlcat(full_path, paths[i], sizeof(full_path));
		ft_strlcat(full_path, "/", sizeof(full_path));
		ft_strlcat(full_path, cmd, sizeof(full_path));
		if (access(full_path, X_OK) == 0)
		{
			ft_free_matrix(paths);
			return (1); // Command found in $PATH and is executable
		}
		i++;
	}
	ft_free_matrix(paths);
	return (0); // Command not found in $PATH
}

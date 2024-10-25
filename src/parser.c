#include "../include/minishell.h"
#include "../include/libft/libft.h"
#include "../include/parser.h"

void	parser(char *input, t_tools *t) //im just trying to deal with "ls -a | wc -l"
{
	char	**tokens;
	t_scmd	*scmd;
	t_token	*lst;

	tokens = ft_split(input, ' ');
	if (!tokens)
		return ;
	lst = token_list(tokens);
	if (!lst)
		return ;
	scmd = simple_command(lst);
	check_exec_command(t, scmd);
}

int	check_exec_command(t_tools *t, t_scmd *scmd)
{
	int pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		if (is_builtin(scmd->args[0]))
		{
			scmd->builtin(t, scmd);
			exit (0);
		}
		else if (is_executable(scmd->args[0]))
		{
			execve(scmd->args[0], scmd->args, NULL);
			perror("execve");
			exit(1);
		}
		else
		{
			printf("%s: command not found", scmd->args[0]);
			exit(127); // exit with command not found status
		}
	}
	else if (pid < 0)
		perror("fork");
	else
		waitpid(pid, &status, 0);
	ft_free_matrix(scmd->args);
	return (0);
}

int is_builtin(char *token)
{
	int len;

	len = ft_strlen(token);
	if (!ft_strncmp(token, "cd", len) || !ft_strncmp(token, "pwd", len) || !ft_strncmp(token, "echo", len) || !ft_strncmp(token, "exit", len))
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

#include "../include/minishell.h"
#include "../include/libft/libft.h"
#include "../include/parser.h"
#include "../include/redirection.h"

int check_exec_command(t_tools *t, t_scmd *scmd)
{
	int prev_fd;
	int has_next;
	int pid;
	int e_status;
	int	status;

	prev_fd = -1;
	while (scmd)
	{
		has_next = scmd->next != NULL;
        if (create_pipe_if_needed(t, has_next, scmd) == -1)
            return (EXIT_FAILURE);
        if (scmd->builtin && !has_next && !scmd->R_HEREDOC_delimiter)
        {
            t->exit_status = scmd->builtin(t, scmd);
            return (t->exit_status);
		}
		pid = fork();
		if (pid == 0)
			execute_child_process(t, scmd, prev_fd, has_next);
		else if (pid < 0)
		{
			perror("fork");
			return (EXIT_FAILURE);
		}
        close_unused_pipes(&prev_fd, t, has_next);
        while (wait(&status) > 0)
			;
		scmd = scmd->next;
	}
	return (EXIT_SUCCESS);
}

int	is_builtin(char *token)
{
	const char	*builtins[] = {"cd", "pwd", "echo", "exit", "export", "unset", "env", "history", NULL};
	int	i;
	int	token_len;

	i = 0;
	token_len = ft_strlen(token);
	while (builtins[i] != NULL)
	{
		if (ft_strncmp(token, builtins[i], token_len) == 0 && ft_strlen(builtins[i]) == token_len)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

char	*is_executable(char *cmd)
{
	char	*path_env;
	char	**paths;
	char	*exec_full_path;
	int		i;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (paths == NULL)
		return (NULL);
	while (paths[i])
	{
		exec_full_path = malloc(ft_strlen(paths[i]) + ft_strlen(cmd) + 2);
		if (exec_full_path == NULL)
		{
			ft_free_matrix(paths);
			return (NULL);
		}
		ft_strlcpy(exec_full_path, paths[i], ft_strlen(paths[i]) + 1);
		ft_strlcat(exec_full_path, "/", ft_strlen(paths[i]) + 2);
		ft_strlcat(exec_full_path, cmd, ft_strlen(paths[i]) + ft_strlen(cmd) + 2);
		if (access(exec_full_path, X_OK) == 0)
		{
			ft_free_matrix(paths);
			return (exec_full_path);
		}
		free(exec_full_path);
		i++;
	}
	ft_free_matrix(paths);
	return (NULL);
}

// void	execute_executable()
// {
// 	pid = fork();
// 	if (pid == 0)
// 		execute_child_process(t, scmd, prev_fd, has_next);
// 	else if (pid < 0)
// 	{
// 		perror("fork");
// 		return (EXIT_FAILURE);
// 	}
// 	finalize_parent_process(&prev_fd, t, has_next);
// }

// void	check_builtin_and_exec(t_scmd *scmd, t_token *t)
// {
// 	scmd->builtin(t, scmd);
// 	return(EXIT_SUCCESS);
// 	finalize_parent_process(&prev_fd, t, has_next);
// }

#include "../include/minishell.h"
#include "../include/libft/libft.h"
#include "../include/parser.h"
#include "../include/redirection.h"

t_exec *init_t_exec(void)
{
    t_exec *e;

    e = malloc(sizeof(t_exec)); // Allocate memory for the struct
    if (!e)
    {
        perror("malloc failed"); // Handle allocation failure
        return (NULL);
    }
    e->prev_fd = -1; // Initialize fields
    e->n = 0;
    return (e); // Return the allocated and initialized struct
}

int	check_exec_command(t_tools *t, t_scmd *scmd)
{
	t_exec	*e;

	e = init_t_exec();
	while (scmd)
	{
		e->has_next = scmd->next != NULL;
		if (create_pipe_if_needed(t, e->has_next, scmd) == -1)
			return (EXIT_FAILURE);
		if (scmd->builtin && !scmd->pipecount && !scmd->redirect_token)
		{
			t->exit_status = scmd->builtin(t, scmd);
			return (t->exit_status);
		}
		e->pid = fork();
		after_fork(t, scmd, e);
		scmd = scmd->next;
	}
	return (wait_for_pids(e->pids, e->n, t));
}

int	is_builtin(char *token)
{
	const char	*func[9];
	int			i;
	size_t		len;

	func[0] = "cd";
	func[1] = "pwd";
	func[2] = "echo";
	func[3] = "exit";
	func[4] = "export";
	func[5] = "unset";
	func[6] = "env";
	func[7] = "history";
	func[8] = NULL;
	i = 0;
	len = ft_strlen(token);
	while (func[i] != NULL)
	{
		if (ft_strncmp(token, func[i], len) == 0 && ft_strlen(func[i]) == len)
			return (1);
		i++;
	}
	return (0);
}

char	*create_full_path(char **paths, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = malloc(ft_strlen(paths[i]) + ft_strlen(cmd) + 2);
		if (!full_path)
		{
			ft_free_matrix(paths);
			return (NULL);
		}
		ft_strlcpy(full_path, paths[i], ft_strlen(paths[i]) + 1);
		ft_strlcat(full_path, "/", ft_strlen(paths[i]) + 2);
		ft_strlcat(full_path, cmd, ft_strlen(paths[i]) + ft_strlen(cmd) + 2);
		if (access(full_path, X_OK) == 0)
		{
			ft_free_matrix(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_matrix(paths);
	return (NULL);
}

char	*is_executable(char *cmd, t_tools *t)
{
	char	*path_env;
	char	**paths;
	char	*full_path;

	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	path_env = ft_getenv("PATH", t);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (paths == NULL)
		return (NULL);
	full_path = create_full_path(paths, cmd);
	return (full_path);
}

int	after_fork(t_tools *t, t_scmd *scmd, t_exec *e)
{
	if (e->pid == 0)
	{
		execute_child_process(t, scmd, e->prev_fd, e->has_next);
		exit(t->exit_status);
	}
	else if (e->pid < 0)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	else
		e->pids[e->n++] = e->pid;
	close_unused_pipes(&e->prev_fd, t, e->has_next);
	return (0);
}

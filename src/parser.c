#include "../include/minishell.h"
#include "../include/libft/libft.h"
#include "../include/parser.h"
#include "../include/redirection.h"

void	parser(char *input, t_tools *t)
{
	char	**tokens;
	t_scmd	*scmd;
	t_token	*lst;

	check_quotes(input);
	tokens = ft_split(input, ' ');
	if (!tokens)
		return ;
	lst = token_list(tokens);
	if (!lst)
		return ;
	scmd = simple_command(lst);
	check_exec_command(t, scmd);
}

char	*format_arg(t_scmd *scmd, char *arg)
{
	if (!check_quotes(arg))
			arg = trim_quotes(arg, scmd);
	else
		return (NULL);
	if (arg[0] == '$' && scmd->quote_token != '\'')
	{
		arg ++;
		arg = getenv(arg);
		if (arg == NULL)
			return (ft_strdup(""));
	}
	return (arg);
}

int	check_quotes(char *arg)
{
	bool	dq;
	bool	sq;
	int		i;

	i = 0;
	dq = false;
	sq = false;
	while (arg[i])
	{
		if (arg[i] == '"' && !sq)
			dq = !dq;
		if (arg[i] == '\'' && !dq)
			sq = !sq;
		i ++;
	}
	if (dq || sq)
	{
		ft_putstr_fd("Error: Unclosed quotes in input.\n", 2);
		return (-1);
	}
	return (0);
}

char	*trim_quotes(char *arg, t_scmd *scmd)
{
	int	i;
	int	z;

	z = ft_strlen(arg) - 1;
	i = 0;
	if ((arg[i] == '\'' && arg[z] == '\'') || (arg[i] == '\"' && arg[z] == '\"'))
	{
		if (arg[i] == '\'' && arg[z] == '\'')
			scmd->quote_token = '\'';
		else
			scmd->quote_token = '\"';
		arg[z] = '\0';
		arg ++;
	}
	return (arg);
}

int	check_exec_command(t_tools *t, t_scmd *scmd)
{
	int pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		handle_redirection(scmd);
		if (is_builtin(scmd->args[0]))
		{
			scmd->builtin(t, scmd);
			exit (0);
		}
		else if (is_executable(scmd->args[0]))
		{
			scmd->exec_path = is_executable(scmd->args[0]); //write it better later
			execve(scmd->exec_path, scmd->args, t->envp);
			perror("execve");
			exit(1);
		}
		else
		{
			printf("minishell: command not found: %s\n", scmd->args[0]);
			exit(127); // exit with command not found status
		}
		scmd->old_fd = dup(STDOUT_FILENO);
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
	if (!ft_strncmp(token, "cd", len) || !ft_strncmp(token, "pwd", len) || !ft_strncmp(token, "echo", len) || !ft_strncmp(token, "exit", len) || !ft_strncmp(token, "export", len) || !ft_strncmp(token, "unset", len) || !ft_strncmp(token, "env", len))
		return (1);
	return(0);
}

char	*is_executable(char *cmd)
{
	char	*path_env;
	char	**paths;
	char    *exec_full_path;
	int     i;

	i = 0;
	path_env = getenv("PATH");
	if (path_env == NULL)
		return (NULL); // PATH not set, command can't be found
	paths = ft_split(path_env, ':');
	if (paths == NULL)
		return (NULL); // Failed to split PATH, exit early
	while (paths[i])
	{
		exec_full_path = malloc(ft_strlen(paths[i]) + ft_strlen(cmd) + 2);
		if (exec_full_path == NULL)
		{
            ft_free_matrix(paths);
            return (NULL);
        }
		ft_strlcpy(exec_full_path, paths[i], sizeof(exec_full_path));
		ft_strlcat(exec_full_path, "/", sizeof(exec_full_path));
		ft_strlcat(exec_full_path, cmd, sizeof(exec_full_path));
		if (access(exec_full_path, X_OK) == 0)
		{
			ft_free_matrix(paths);
			return (exec_full_path); // Command found in $PATH and is executable
		}
		free(exec_full_path);
		i++;
	}
	ft_free_matrix(paths);
	return (NULL); // Command not found in $PATH
}

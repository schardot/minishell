#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/redirection.h"

/*• Your shell must implement the following builtins:
◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options

### For other commands:
For any commands **not** listed as built-ins (like `ls`, `grep`, `cat`, etc.), you'll use the `execve()` function to execute them. This is how standard shells (like bash or zsh) execute external commands.
*/


int builtinecho(t_tools *t, t_scmd *scmd)
{
	int		flag;
	char	*output;
	char	*arg;
	char	*temp;
	int		i;

	if (!scmd->args[1])
		printf("\n");
	if (!ft_strncmp(scmd->args[1], "-n", ft_strlen(scmd->args[1])))
		flag = 1;
	else
		flag = 0;
	i = flag + 1;
	arg = ft_strdup("");
	while (scmd->args[i])
	{
		output = format_arg(scmd, scmd->args[i]);
		if (!output)
		{
			//free(arg);
			return (-1);
		}
		temp = ft_strjoin(arg, output);
		//free (arg);
		arg = temp;
		temp = ft_strjoin(arg, " ");
        //free(arg);
        arg = temp;
		i ++;
	}
	ft_putstr_fd(arg, STDOUT_FILENO);
	if (scmd->num_redirections > 0)
	{
		handle_redirection(scmd);
		restore_stdout(scmd);
	}
	//printf("%s", arg);
	if (flag == 0)
		printf("\n");
	//free(arg);
	return (0);
}


int	builtincd(t_tools *t, t_scmd *node)
{
	(void)t;
	if (chdir(node->args[1]) != 0)
		printf("Error: %s\n", strerror(errno));
	return (0);
	/* - - - - - - - - - - - - - - - - - - - - - CHAT GPT - - - - - - - - - - - - - - - - - - - - - - - - - - -
	**cd** (only with relative or absolute paths):
   - Changes the current working directory.
   - You don't need to handle complex options like `cd -` to switch back to the previous directory. Just handle `cd` with an absolute or relative path.*/
}

int	builtinpwd(t_tools *t, t_scmd *node)
{
	(void)t;
	(void)node;
	char	buffer[PATH_MAX];

	if (getcwd(buffer, sizeof(buffer)))
		printf("%s\n", buffer);
	else
		perror("getcwd() error");
	return (0);
}

int	builtinexport(t_tools *t, t_scmd *node)
{
	/* - - - - - - - - - - - - - - - - - - - - - CHAT GPT - - - - - - - - - - - - - - - - - - - - - - - - - - -
	**export** (with no options):
   - Sets environment variables.
   - Example: `export VAR=value` sets `VAR` in the environment.*/
	(void)node;
	(void)t;
	return (0);
}

int builtinunset(t_tools *t, t_scmd *scmd)
{
	if (scmd->argsc == 1)
		return (0); // $unset does nothing
	if (check_unset_args(scmd))
	{
		printf("minishell: unset: \'%s\': not a valid identifier\n", scmd->args[1]);
		return (1);
	}
	return (0);
}

int check_unset_args(t_scmd *scmd)
{
	if (!ft_isalpha(scmd->args[1][0]))
		return (1);
	//there are more examples of whats an invalid argument, but for now i just want to build the idea of the thing.
	return (0);
}

int	builtinenv(t_tools *t, t_scmd *node)
{
	char	**aux;
	int	i;

	aux = t->envp;
	i = 0;
	while(aux[i])
	{
		printf("%s\n", aux[i]);
		i ++;
	}
	(void)node;
	return (0);
}

int	builtinexit(t_tools *t, t_scmd *node)
{
	/* - - - - - - - - - - - - - - - - - - - - - CHAT GPT - - - - - - - - - - - - - - - - - - - - - - - - - - -
   **exit** (with no options):
   - Exits the shell.

   Example:
   - `exit` simply terminates the shell.
   - You could also support an optional exit status (e.g., `exit 42`).

   Expected Behavior:
exit: Exits with status 0.
exit 42: Exits with status 42.
exit abc: Prints an error exit: abc: numeric argument required and exits with status 255.
exit 1 2: Prints an error exit: too many arguments and does not exit.
*/
	(void)node;
	(void)t;
	return (0);
}
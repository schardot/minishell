#include "../include/minishell.h"
#include "../include/parser.h"

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
	int		i;
	char	*arg;

	if (!ft_strncmp(scmd->args[1], "-n", ft_strlen(scmd->args[1])))
		i = 2;
	else
		i = 1;
	arg = ft_strdup(scmd->args[i]);
	if (!arg)
		return (-1);
	if (!check_quotes(arg))
		arg = trim_quotes(arg, scmd);
	else
		return (1);
	if (arg[0] == '$' && scmd->quote_token != '\'')
	{
		arg ++;
		arg = getenv(arg);
		if (arg == NULL)
			return (-1);
	}
	printf("%s", arg);
	if (i == 1)
		printf("\n");
	//free (arg);
	return (0);
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
		i++;
	}
	if (dq || sq)
	{
		ft_putstr_fd("Error: Unclosed quotes in input.\n", 2);
		free(arg);
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

int	builtinunset(t_tools *t, t_scmd *node)
{
	/* - - - - - - - - - - - - - - - - - - - - - CHAT GPT - - - - - - - - - - - - - - - - - - - - - - - - - - -
   **unset** (with no options):
   - Removes environment variables.
   - Example: `unset VAR` removes `VAR` from the environment.*/
	(void)node;
	(void)t;
	return (0);
}

int	builtinenv(t_tools *t, t_scmd *node)
{
	/* - - - - - - - - - - - - - - - - - - - - - CHAT GPT - - - - - - - - - - - - - - - - - - - - - - - - - - -
  **env** (with no options or arguments):
   - Prints all the current environment variables.*/
	(void)node;
	(void)t;
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
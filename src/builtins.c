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


int builtinecho(t_tools *t, t_scmd *node)
{
	if (!ft_strncmp(node->args[1], "-n", ft_strlen(node->args[1])))
		printf("%s", node->args[2]);
	else
		printf("%s\n", node->args[1]);
	/* - - - - - - - - - - - - - - - - - - - - - CHAT GPT - - - - - - - - - - - - - - - - - - - - - - - - - - -
	1. **echo** (with the `-n` option):
	- Prints the provided text and, by default, adds a newline at the end. The `-n` option suppresses that newline.
	Examples:
	- `echo hello world` → prints "hello world\n"
	- `echo -n hello world` → prints "hello world" (no newline)
	*/

	// - - - - - - - - - - - - - - - - THIS BELOW IS FROM THE SUBJECT: - - - - - - - - - - - - - - - - - - - - -
	// • Handle ’ (single quote)which should prevent the shell from interpreting the metacharacters in the quoted sequence.
	// • Handle " (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign).
	// Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon).
	(void)t;
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
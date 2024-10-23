#include "../include/minishell.h"

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
void    execute_builtin(char **cmd, int len)
{
    if (!ft_strncmp(cmd[0], "cd", len))
        cd(cmd[1]);
    // else if (!ft_strncmp(cmd, "echo", len))
    //     echo();
    else if (!ft_strncmp(cmd[0], "pwd", len))
        pwd();
    // else if (!ft_strncmp(cmd, "export", len))
    //     export();
    // else if (!ft_strncmp(cmd, "unset", len))
    //     unset();
    // else if (!ft_strncmp(cmd, "env", len))
    //     env();
    // else if (!ft_strncmp(cmd, "exit", len))
    //     exit();
}

void    echo(void)
{
    /* - - - - - - - - - - - - - - - - - - - - - CHAT GPT - - - - - - - - - - - - - - - - - - - - - - - - - - -
    1. **echo** (with the `-n` option):
   - Prints the provided text and, by default, adds a newline at the end. The `-n` option suppresses that newline.

   Examples:
   - `echo hello world` → prints "hello world\n"
   - `echo -n hello world` → prints "hello world" (no newline)
    */

    // - - - - - - - - - - - - - - - - THIS BELOW IS FROM THE SUBJECT: - - - - - - - - - - - - - - - - - - - - -
    //• Handle ’ (single quote)which should prevent the shell from interpreting the metacharacters in the quoted sequence.
    //• Handle " (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign).
    //Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon).
}

void    cd(const char *path)
{
    if (chdir(path) != 0)
        printf("Error: %s\n", strerror(errno));
    /* - - - - - - - - - - - - - - - - - - - - - CHAT GPT - - - - - - - - - - - - - - - - - - - - - - - - - - -
    **cd** (only with relative or absolute paths):
   - Changes the current working directory.
   - You don't need to handle complex options like `cd -` to switch back to the previous directory. Just handle `cd` with an absolute or relative path.*/
}

void    pwd(void)
{
    char    buffer[PATH_MAX];

    if (getcwd(buffer, sizeof(buffer)))
        printf("%s\n", buffer);
    else
        perror("getcwd() error");
}

void export(void)
{
    /* - - - - - - - - - - - - - - - - - - - - - CHAT GPT - - - - - - - - - - - - - - - - - - - - - - - - - - -
    **export** (with no options):
   - Sets environment variables.
   - Example: `export VAR=value` sets `VAR` in the environment.*/
}

void unset(void)
{
    /* - - - - - - - - - - - - - - - - - - - - - CHAT GPT - - - - - - - - - - - - - - - - - - - - - - - - - - -
   **unset** (with no options):
   - Removes environment variables.
   - Example: `unset VAR` removes `VAR` from the environment.*/
}

void env(void)
{
    /* - - - - - - - - - - - - - - - - - - - - - CHAT GPT - - - - - - - - - - - - - - - - - - - - - - - - - - -
  **env** (with no options or arguments):
   - Prints all the current environment variables.*/
}

void mexit(void)
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
}
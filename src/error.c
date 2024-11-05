#include "../include/minishell.h"
#include "../include/libft/libft.h"
#include "../include/parser.h"
#include "../include/redirection.h"

void ft_error(t_error type, char *cmd, t_scmd *scmd)
{
    static char *err[] = {
        "No such file or directory",
        "Not a directory",
        "Permission denied",
        "Unknown error"};
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(cmd, 2);
    ft_putstr_fd(": ", 2);

    if (type == E_NOT_A_DIR || type == E_NO_SUCH_FILE || type == E_PERMISSION_DENIED)
    {
        ft_putstr_fd(scmd->args[1], 2);
        ft_putstr_fd(": ", 2);
        ft_putendl_fd(err[type], 2);
    }
}
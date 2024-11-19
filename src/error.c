/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nataliaschardosim <nataliaschardosim@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:24:44 by codespace         #+#    #+#             */
/*   Updated: 2024/11/19 10:21:55 by nataliascha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/libft/libft.h"
#include "../include/parser.h"
#include "../include/redirection.h"

void	update_exit(t_error type, t_tools *t);
char    **make_error_str(void);

void ft_error(t_error type, char *cmd, char *inv_arg, t_tools *t)
{
	char    **err;

    err = make_error_str();
    ft_fprintf(2, "minishell: ");
    if (cmd)
        ft_fprintf(2, "%s: ", cmd);
	if (inv_arg)
    {
        if (type == E_NOT_A_VALID_ID)
            ft_fprintf(2, "`%s': ", inv_arg);
        else
            ft_fprintf(2, "%s: ", inv_arg);
    }
	ft_putendl_fd(err[type], 2);
	update_exit(type, t);
}


void	update_exit(t_error type, t_tools *t)
{
	if (type == E_COMMAND_NOT_FOUND)
		t->exit_status = 127;
	else if (type == E_SYNTAX_ERROR || type == E_NUM_ARG_REQUIRED)
		t->exit_status = 2;
	else if (type == E_NOT_A_VALID_ID || type == E_NOT_A_DIR || type == E_NO_SUCH_FILE)
		t->exit_status = 127;
	else if (type == E_TOO_MANY_ARGS || type == E_PERMISSION_DENIED)
		t->exit_status = 1;
	else
		t->exit_status = 0;
}

char **make_error_str(void)
{
    static char *err[] = {
        "No such file or directory",
        "Not a directory",
        "Permission denied",
        "not a valid identifier",
        "numeric argument required",
        "too many arguments",
        "command not found",
        "HOME not set",
        "syntax error near unexpected token",
        "invalid option",
        "Unknown error",
        NULL};
    return (err);
}

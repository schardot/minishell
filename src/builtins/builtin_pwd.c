/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nataliaschardosim <nataliaschardosim@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:50:26 by nataliascha       #+#    #+#             */
/*   Updated: 2024/11/18 15:17:16 by nataliascha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/minishell.h"

static int check_pwd_args(t_scmd *scmd, t_tools *t);

int builtinpwd(t_tools *t, t_scmd *scmd)
{
	char	buffer[PATH_MAX];

    if (check_pwd_args(scmd, t) == 1)
        return (EXIT_FAILURE);
    if (getcwd(buffer, sizeof(buffer)))
	{
		printf("%s\n", buffer);
		return (EXIT_SUCCESS);
	}
	else
	{
		perror("getcwd() error");
		return (EXIT_FAILURE);
	}
}

static int check_pwd_args(t_scmd *scmd, t_tools *t)
{
    char *arg;

    arg = scmd->args[1];
    if (arg && arg[1] && arg[0] == '-' && arg[1] != '-')
    {
        ft_error(E_INVALID_OPTION, "pwd", arg, t);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

/* pwd doesnt need arguments, but it checks the first one.
it only reacts if its a flag (starting with -).
so pwd -a doesnt work (bash: pwd: -a: invalid option) // EXIT 1,
but pwd -- just does pwd. and pwd - also isnt a problem
BUT if you pass multiple arguments, it only checks the first one.
pwd -a b  ------- complains about -a
pwd a -b  ------- says nothing and does pwd
*/
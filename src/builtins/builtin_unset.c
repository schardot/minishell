/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nataliaschardosim <nataliaschardosim@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:50:30 by nataliascha       #+#    #+#             */
/*   Updated: 2024/11/01 11:03:32 by nataliascha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/redirection.h"

int builtinunset(t_tools *t, t_scmd *scmd)
{
    const char *var;
    int var_len;
    int i;

    if (scmd->argsc != 2)
        return (EXIT_FAILURE);
    if (check_unset_args(scmd))
    {
        printf("minishell: unset: \'%s\': not a valid identifier\n", scmd->args[1]);
        return (EXIT_FAILURE);
    }
    var = scmd->args[1];
    var_len = ft_strlen(var);
    i = 0;
    while (t->envp[i])
    {
        if (ft_strncmp(t->envp[i], var, var_len) == 0 && t->envp[i][var_len] == '=')
        {
            free(t->envp[i]);
            while (t->envp[i] != NULL)
            {
                t->envp[i] = t->envp[i + 1];
                i++;
            }
            return (EXIT_SUCCESS);
        }
        i++;
    }
    return (EXIT_SUCCESS);
}

int check_unset_args(t_scmd *scmd)
{
    if (!ft_isalpha(scmd->args[1][0]))
        return (EXIT_FAILURE);
    // there are more examples of whats an invalid argument, but for now i just want to build the idea of the thing.
    return (EXIT_SUCCESS);
}

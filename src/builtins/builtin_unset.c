/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:50:30 by nataliascha       #+#    #+#             */
/*   Updated: 2024/11/05 13:50:05 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/redirection.h"

int builtinunset(t_tools *t, t_scmd *scmd)
{
    const char  *var;
    int         var_len;
    int         i;

    if (check_unset_args(scmd))
        return (EXIT_FAILURE);
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
    int i;
    int j;

    if (!scmd->args[1]) //print that crazy list
        i = 0; //just a placeholder so the compiler is ok
    j = 1;
    while (scmd->args[j])
    {
        i = 0;
        while (scmd->args[j][i])
        {
            if (!ft_isalnum(scmd->args[j][i]) && !(scmd->args[j][i] == '_'))
            {
                printf("minishell: unset: \'%s\': not a valid identifier\n", scmd->args[j]);
                return (EXIT_FAILURE);
            }
            i++;
        }
        j ++;
    }
    return (EXIT_SUCCESS);
}

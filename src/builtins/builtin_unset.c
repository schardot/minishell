/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nataliaschardosim <nataliaschardosim@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:50:30 by nataliascha       #+#    #+#             */
/*   Updated: 2024/11/21 15:08:47 by nataliascha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/minishell.h"

int	builtinunset(t_tools *t, t_scmd *scmd)
{
	if (check_unset_args(scmd, t))
		return (EXIT_FAILURE);
	else if (scmd->args[1])
		create_new_envp(scmd, t);
	return (EXIT_SUCCESS);
}

int	check_unset_args(t_scmd *s, t_tools *t)
{
	int     i;
	int     j;

    if (s->args[1] && s->args[1][1] && s->args[1][0] == '-' && s->args[1][1] != '-')
    {
        ft_error(E_INVALID_OPTION, "unset", s->args[1], t);
        return (EXIT_FAILURE);
    }
    j = 1;
    while (s->args[j])
	{
        if (s->args[j][0] == '\0')
        {
            ft_error(E_NOT_A_VALID_ID, s->args[0], s->args[j], t);
            t->exit_status = 1; // Indicate failure
            j++;
            continue;
        }
        i = 0;
        while (s->args[j][i]) //check if a loop is necessary or if it quits in the first error
        {
            if (!ft_isalnum(s->args[j][i]) && !(s->args[j][i] == '_'))
                ft_error(E_NOT_A_VALID_ID, s->args[0], s->args[j], t);
            i++;
		}
		j ++;
	}
	if (t->exit_status == 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	create_new_envp(t_scmd *scmd, t_tools *t)
{
	const char	*var;
	int			vlen;
	int			i;

	var = scmd->args[1];
	vlen = ft_strlen(var);
	i = 0;
	while (t->envp[i])
	{
		if (ft_strncmp(t->envp[i], var, vlen) == 0 && t->envp[i][vlen] == '=')
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

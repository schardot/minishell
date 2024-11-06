/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:50:19 by nataliascha       #+#    #+#             */
/*   Updated: 2024/11/06 17:42:07 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"

int	builtinenv(t_tools *t, t_scmd *scmd)
{
	int	i;

	i = 0;
	if (scmd->args[1])
	{
		ft_error(E_NO_SUCH_FILE, "env", scmd->args[1], t);
		return (EXIT_FAILURE);
	}
	while (t->envp[i])
	{
		printf("%s\n", t->envp[i]);
		i ++;
	}
	return (EXIT_SUCCESS);
}

char	*ft_getenv(char *env, t_tools *t)
{
	int	env_len;
	int	i;

	i = 0;
    env_len = strlen(env);
	while (t->envp[i])
	{
        if (ft_strncmp(env, t->envp[i], env_len) == 0)
		{
            if (t->envp[i][env_len] == '=')
                return (ft_strdup(t->envp[i]));
        }
		i++;
	}
	return (NULL);
}

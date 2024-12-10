/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_to_arr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nataliaschardosim <nataliaschardosim@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:38:12 by nataliascha       #+#    #+#             */
/*   Updated: 2024/10/24 12:38:23 by nataliascha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_arrcat(char **arr, char *str, int len)
{
	char	**new;

	if (!str || len < 0)
		return (NULL);
	new = ft_realloc(arr, (len + 1) * sizeof(char *), \
	(len + 2) * sizeof(char *));
	if (!new)
	{
		ft_free_matrix(arr);
		return (NULL);
	}
	new[len] = ft_strdup(str);
	if (!new[len])
	{
		ft_free_matrix(new);
		new = NULL;
		return (NULL);
	}
	new[len + 1] = NULL;
	return (new);
}

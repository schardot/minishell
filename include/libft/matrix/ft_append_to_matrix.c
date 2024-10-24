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

char	**ft_append_to_array(char **arr, char *str, int len)
{
	char	**new;

	new = ft_realloc(arr, (len + 1) * sizeof(char *), \
	(len + 2) * sizeof(char *));
	if (!new)
		return (NULL);
	new[len] = ft_strdup(str);
	if (!new[len])
		return (NULL);
	new[len + 1] = NULL;
	free (str);
	return (new);
}

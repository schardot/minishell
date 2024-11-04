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

	new = ft_realloc(arr, (len + 1) * sizeof(char *), \
	(len + 2) * sizeof(char *));
	if (!new)
	{
		free(str); // Free str if realloc fails and str was dynamically allocated
		return (NULL);
	}
	new[len] = ft_strdup(str);
	if (!new[len])
	{
		free(str);			 // Free str before returning NULL if strdup fails
		ft_free_matrix(new); // Free the new array if strdup fails
		return (NULL);
	}
	new[len + 1] = NULL;
	free (str);
	return (new);
}

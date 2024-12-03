/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:46:22 by nataliascha       #+#    #+#             */
/*   Updated: 2024/12/02 22:51:22 by nleite-s         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../libft.h"

char	**ft_matrixdup(char **matrix, int height)
{
	int		i;
	char	**newmatrix;

	if (height <= 0 || !matrix)
		return (NULL);
	newmatrix = (char **)malloc((height + 1) * sizeof(char *));
	if (!newmatrix)
		return (NULL);
	i = 0;
	while (i < height)
	{
		newmatrix[i] = ft_strdup(matrix[i]);
		if (!newmatrix[i])
		{
			 while (i > 0)
				free(newmatrix[--i]);
			free(newmatrix);
			return (NULL);
		}
		i ++;
	}
	newmatrix[height] = NULL;
	return (newmatrix);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:30:09 by nleite-s          #+#    #+#             */
/*   Updated: 2024/12/03 20:30:12 by nleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nataliaschardosim <nataliaschardosim@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:46:22 by nataliascha       #+#    #+#             */
/*   Updated: 2024/10/24 12:46:24 by nataliascha      ###   ########.fr       */
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
			ft_free_matrix(newmatrix);
			return (NULL);
		}
		i ++;
	}
	newmatrix[i] = NULL;
	return (newmatrix);
}

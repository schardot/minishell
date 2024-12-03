/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 20:30:56 by nleite-s          #+#    #+#             */
/*   Updated: 2024/12/03 20:30:57 by nleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return (NULL);
	i = 0;
	while (matrix[i])
	{
		free (matrix[i]);
		i ++;
	}
	free (matrix);
	return (NULL);
}

/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:46:41 by nataliascha       #+#    #+#             */
/*   Updated: 2024/12/02 21:38:38 by nleite-s         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../libft.h"

void	ft_free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i])
	{
		free (matrix[i]);
		i ++;
	}
	free (matrix);
}

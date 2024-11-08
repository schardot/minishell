/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str2dlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:24:50 by nataliascha       #+#    #+#             */
/*   Updated: 2024/11/07 09:38:54 by nleite-s         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../libft.h"

size_t	ft_str2dlen(char **array)
{
	size_t	count;

	if (!array || !*array)
		return (0);
	count = 0;
	while (array[count] != NULL)
		count++;
	return (count);
}

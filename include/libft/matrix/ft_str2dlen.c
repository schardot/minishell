/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str2dlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 08:30:40 by nleite-s          #+#    #+#             */
/*   Updated: 2024/11/25 08:30:41 by nleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

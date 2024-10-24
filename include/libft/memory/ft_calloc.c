/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nataliaschardosim <nataliaschardosim@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 19:26:23 by nataliascha       #+#    #+#             */
/*   Updated: 2024/10/16 12:50:24 by nataliascha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*arr;

	if (count == 0 || size == 0)
	{
		arr = malloc(0);
		return (arr);
	}
	if (size > SIZE_MAX / count)
		return (NULL);
	arr = malloc (count * size);
	if (arr != NULL)
		ft_bzero(arr, count * size);
	return (arr);
}

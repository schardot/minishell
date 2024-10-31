/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:47:48 by codespace         #+#    #+#             */
/*   Updated: 2024/10/31 12:47:49 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmem(const void* big, size_t big_len, const void* little, size_t little_len)
{
	const char	*h;
	const char	*n;
	size_t		i;

	if (little_len == 0)
		return ((void *)big);
	if (little_len > big_len)
		return (NULL);
	h = (const char *)big;
	n = (const char *)little;
	i = 0;
	while (i <= big_len - little_len)
	{
		if (h[i] == n[0] && !ft_memcmp(h + i, n, little_len))
			return (void *)(h + i);
		i ++;
	}
	return (NULL);
}
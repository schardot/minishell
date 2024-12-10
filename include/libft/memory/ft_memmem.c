/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekechedz <ekechedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 08:33:26 by nleite-s          #+#    #+#             */
/*   Updated: 2024/11/25 18:51:27 by ekechedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmem(void *big, size_t blen, void *lil, size_t lillen)
{
	char	*h;
	char	*n;
	size_t	i;

	if (lillen == 0)
		return ((void *)big);
	if (lillen > blen)
		return (NULL);
	h = (char *)big;
	n = (char *)lil;
	i = 0;
	while (i <= blen - lillen)
	{
		if (h[i] == n[0] && !ft_memcmp(h + i, n, lillen))
			return ((void *)(h + i));
		i ++;
	}
	return (NULL);
}

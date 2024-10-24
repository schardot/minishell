/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nataliaschardosim <nataliaschardosim@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:46:15 by nleite-s          #+#    #+#             */
/*   Updated: 2024/10/16 12:50:24 by nataliascha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*s;
	char	*d;
	size_t	i;

	if (src == NULL && dst == NULL)
		return (NULL);
	d = (char *)dst;
	s = (char *)src;
	if (s < d)
	{
		while (len -- > 0)
		{
			d[len] = s[len];
		}
	}
	else
	{
		i = 0;
		while (i < len)
		{
			d[i] = s[i];
			i ++;
		}
	}
	return (dst);
}

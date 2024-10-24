/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nataliaschardosim <nataliaschardosim@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:32:32 by nleite-s          #+#    #+#             */
/*   Updated: 2024/10/16 12:50:24 by nataliascha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;
	int		j;

	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	j = 0;
	i = dstlen;
	if (size <= dstlen)
		return (srclen + size);
	while (i < size - 1 && src[j] != '\0')
	{
		dst[i] = src[j];
		i ++;
		j ++;
	}
	dst[i] = '\0';
	return (dstlen + srclen);
}

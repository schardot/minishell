/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nataliaschardosim <nataliaschardosim@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:42:54 by nleite-s          #+#    #+#             */
/*   Updated: 2024/10/16 12:50:24 by nataliascha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*one;
	unsigned char	*two;

	one = (unsigned char *) s1;
	two = (unsigned char *) s2;
	if (n == 0)
		return (0);
	i = 0;
	while (i < n)
	{
		if (*one != *two)
		{
			return (*one - *two);
		}
		one ++;
		two ++;
		i ++;
	}
	return (0);
}

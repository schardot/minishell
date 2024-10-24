/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str2dlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nataliaschardosim <nataliaschardosim@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:24:50 by nataliascha       #+#    #+#             */
/*   Updated: 2024/10/24 12:45:58 by nataliascha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_str2dlen(char **array)
{
	size_t	count;

	count = 0;
	while (array[count] != NULL)
		count++;
	return (count);
}

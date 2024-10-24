/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nataliaschardosim <nataliaschardosim@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:02:11 by nleite-s          #+#    #+#             */
/*   Updated: 2024/10/16 12:49:36 by nataliascha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*aux;

	aux = lst;
	i = 0;
	if (!lst)
		return (0);
	while (aux)
	{
		i++;
		aux = aux->next;
	}
	return (i);
}

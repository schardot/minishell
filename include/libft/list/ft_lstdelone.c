/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nataliaschardosim <nataliaschardosim@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:05:12 by nleite-s          #+#    #+#             */
/*   Updated: 2024/10/16 12:49:21 by nataliascha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void
*))
{
	if (!lst)
		return ;
	if (del)
		del(lst->content);
	free(lst);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nataliaschardosim <nataliaschardosim@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:31:16 by nleite-s          #+#    #+#             */
/*   Updated: 2024/10/16 12:49:02 by nataliascha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	long	longnb;

	longnb = nb;
	if (longnb < 0)
	{
		longnb = -longnb;
		ft_putchar_fd('-', fd);
	}
	if (longnb < 10)
	{
		ft_putchar_fd('0' + longnb, fd);
	}
	else
	{
		ft_putnbr_fd(longnb / 10, fd);
		ft_putnbr_fd(longnb % 10, fd);
	}
}

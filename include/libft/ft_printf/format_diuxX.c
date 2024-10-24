/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_diuxX.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nataliaschardosim <nataliaschardosim@st    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 22:23:14 by nataliascha       #+#    #+#             */
/*   Updated: 2024/10/22 16:37:35 by nataliascha      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printnbr(int nb)
{
	int	len;

	len = 0;
	if (nb == INT_MIN)
	{
		len += ft_printstr("-2147483648");
		return (len);
	}
	if (nb < 0)
	{
		nb = -nb;
		len += ft_printchar('-');
	}
	if (nb < 10)
		len += ft_printchar('0' + nb);
	else
	{
		len += ft_printnbr(nb / 10);
		len += ft_printnbr(nb % 10);
	}
	return (len);
}

int	ft_printnbr_unsigned(unsigned int nb)
{
	int	len;

	len = 0;
	if (nb < 10)
		len += ft_printchar('0' + nb);
	else
	{
		len += ft_printnbr_unsigned(nb / 10);
		len += ft_printnbr_unsigned(nb % 10);
	}
	return (len);
}

int	fft_putnbr_base(unsigned int nbr, const char *base)
{
	int				len;
	unsigned int	base_len;

	len = 0;
	base_len = ft_strlen(base);
	if (nbr < base_len)
		len += ft_printchar(base[nbr]);
	else
	{
		len += fft_putnbr_base(nbr / base_len, base);
		len += fft_putnbr_base(nbr % base_len, base);
	}
	return (len);
}

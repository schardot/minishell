/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nleite-s <nleite-s@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 08:26:35 by nleite-s          #+#    #+#             */
/*   Updated: 2024/11/25 08:26:37 by nleite-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	handle_string(va_list args, int fd);
static void	handle_num(va_list args, int fd);
static void	handle_char(va_list args, int fd);

void	ft_fprintf(int fd, const char *format, ...)
{
	va_list		args;
	const char	*p;

	va_start(args, format);
	p = format;
	while (*p)
	{
		if (*p == '%' && *(p + 1))
		{
			p ++;
			if (*p == 's')
				handle_string(args, fd);
			else if (*p == 'd')
				handle_num(args, fd);
			else if (*p == 'c')
				handle_char(args, fd);
			else
				write(fd, p, 1);
		}
		else
			write(fd, p, 1);
		p ++;
	}
	va_end(args);
}

static void	handle_string(va_list args, int fd)
{
	char	*str;

	str = va_arg(args, char *);
	ft_putstr_fd(str, fd);
}

static void	handle_num(va_list args, int fd)
{
	int	num;

	num = va_arg(args, int);
	ft_putnbr_fd(num, fd);
}

static void	handle_char(va_list args, int fd)
{
	char	c;

	c = (char)va_arg(args, int);
	write(fd, &c, 1);
}

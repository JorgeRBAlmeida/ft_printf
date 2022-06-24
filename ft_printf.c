/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joalmeid <joalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:10:15 by joalmeid          #+#    #+#             */
/*   Updated: 2022/06/24 13:05:29 by joalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_arg(char c, va_list args);

int	ft_printf(const char *src, ...)
{
	va_list	args;
	int		printed;
	int		index;

	index = -1;
	printed = 0;
	if (!src)
		return (0);
	va_start(args, src);
	while (src[++ index])
	{
		if (src[index] == '%')
		{
			index ++;
			if (ft_strchr("cspdiuxX%", src[index]))
				printed += print_arg(src[index], args);
		}
		else
			printed += ft_putchar_len(src[index], 1);
	}
	va_end(args);
	return (printed);
}

static int	print_arg(char c, va_list args)
{
	if (c == '%')
		return (ft_putchar_len('%', 1));
	else if (c == 'c')
		return (ft_putchar_len((va_arg(args, int)), 1));
	else if (c == 's')
		return (ft_putstr_len((va_arg(args, char *)), 1));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr_len(va_arg(args, int), 1));
	else if (c == 'u')
		return (ft_putnbase_u(va_arg(args, unsigned int), 1, 10, 'x'));
	else if (c == 'x')
		return (ft_putnbase_u(va_arg(args, unsigned int), 1, 16, 'x'));
	else if (c == 'X')
		return (ft_putnbase_u(va_arg(args, unsigned int), 1, 16, 'X'));
	else if (c == 'p')
	{
		write(1, "0x", 2);
		return (ft_putnbase_u(va_arg(args, unsigned long), 1, 16, 'x') + 2);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joalmeid <joalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 09:10:35 by joalmeid          #+#    #+#             */
/*   Updated: 2022/06/24 13:04:54 by joalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	putnbase_u_len(unsigned long n, unsigned long base);
static int	putnbr_len(long n);

int	ft_putchar_len(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_putnbr_len(long n, int fd)
{
	int	len;

	len = putnbr_len(n);
	if (n < 0)
	{
		n = -n;
		ft_putchar_len('-', fd);
	}
	if (n >= 0 && n <= 9)
		ft_putchar_len((n + '0'), fd);
	else
	{
		ft_putnbr_len((n / 10), fd);
		ft_putnbr_len((n % 10), fd);
	}
	return (len);
}

int	ft_putnbase_u(unsigned long nbr, int fd, int base, char type)
{
	int	len;

	if (nbr >= 0 && nbr <= 9)
		ft_putchar_len((nbr + 48), fd);
	else if ((base == 16) && (type == 'x') && (nbr >= 10 && nbr <= 15))
		ft_putchar_len((nbr + 87), fd);
	else if ((base == 16) && (type == 'X') && (nbr >= 10 && nbr <= 15))
		ft_putchar_len((nbr + 55), fd);
	else
	{
		ft_putnbase_u((nbr / base), fd, base, type);
		ft_putnbase_u((nbr % base), fd, base, type);
	}
	len = putnbase_u_len(nbr, base);
	return (len);
}

static int	putnbase_u_len(unsigned long n, unsigned long base)
{
	int	len;

	len = 1;
	while (n > (base - 1))
	{
		n = n / base;
		len ++;
	}
	return (len);
}

static int	putnbr_len(long n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		len ++;
		n = -n;
	}
	while (n > 9)
	{
		n = n / 10;
		len ++;
	}
	return (len);
}

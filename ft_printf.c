/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joalmeid <joalmeid@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:10:15 by joalmeid          #+#    #+#             */
/*   Updated: 2022/06/24 10:27:37 by joalmeid         ###   ########.fr       */
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
			else
				return (-1);
		}
		else
			printed += ft_putchar_len(src[index], 1);
	}
	va_end(args);
	return (printed);
}

static int	print_arg(char c, va_list args)
{
	if(c == '%')
		return (ft_putchar_len('%', 1));
	else if(c == 'c')
		return (ft_putchar_len((va_arg(args, int)), 1));
	else if(c == 's')
		return (ft_putstr_len((va_arg(args, char *)), 1));
	else if(c == 'd' || c == 'i')
		return (ft_putnbr_len(va_arg(args, int), 1));
	else if(c == 'u')
		return (ft_putnbase_u(va_arg(args, unsigned int), 1, 10, 'x'));
	else if(c == 'x')
		return (ft_putnbase_u(va_arg(args, unsigned int), 1, 16, 'x'));
	else if(c == 'X')
		return (ft_putnbase_u(va_arg(args, unsigned int), 1, 16, 'X'));
	else if(c == 'p')
	{
		write(1, "0x", 2);
		return (ft_putnbase_u(va_arg(args, unsigned long), 1, 16, 'x') + 2);
	}
	return (0);
}

/* #include <limits.h>
#include <stdio.h>
int	main(void)
{
	//int	t = -10000;
	//char str[] = "hello!";
	ft_printf("\nreturn ft_printf:\t|%i|\n", ft_printf("bbbbbbbbb'%%%'"));
	printf("\nreturn printf:\t|%i|\n", printf("bbbbbbbbb'%%%'"));
	//void *p;
	//ft_printf("\nreturn ft_printf:\t|%i|\n\n", ft_printf("%p%p", ULONG_MAX, -ULONG_MAX));
	//printf("\nreturn printf:\t|%i|\n", printf("%p%p", (long long *)ULONG_MAX, (long long *)-ULONG_MAX));

	//printf("%d", ft_printf("test%s", str));
	 
} */

/* int	ft_isascii(int c)
{
	if ((char)c >= 0 && (char)c <= 127)
		return (1);
	return (0);
}

int	main(void)
{
	char	src[5] = "% ";

	src[1] = 0;
	while(ft_isascii(src[1]))
	{
		printf("%i |%%%c |sainda printf -->\t", src[1], src[1]);
		if (src[1] == 83 || src[1] == 110 ||  src[1] == 115)
		{
			//src[1] ++;
			//printf("%m");
		}
		else
		{
			printf("|");
			printf(src);
			printf("|");

		}
		printf("\n");
		src[1] ++;
	}
} */
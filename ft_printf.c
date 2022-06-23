/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joalmeid <joalmeid@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:10:15 by joalmeid          #+#    #+#             */
/*   Updated: 2022/06/23 09:07:24 by joalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

size_t		ft_strlen(const char *src);
static int	print_arg(char c, va_list args);

size_t		ft_strlen(const char *src);
char		*ft_strchr(const char *s, int c);
int			ft_putstr_fd(char *s, int fd);
int			ft_putchar_fd(char c, int fd);
static int	putnbase_len(long long n, int base);
int			ft_putnbase_fd(long long nbr, int fd, int base, char x);

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
			if (!src[index])
				break ;
		}
		else
			ft_putchar_fd(src[index], 1);
	}
	va_end(args);
	printed += index;
	return (printed);
}

/* STATICS */

static int	print_arg(char c, va_list args)
{
	if(c == '%')
		return (ft_putchar_fd('%', 1) - 1);
	else if(c == 'c')
		return (ft_putchar_fd((va_arg(args, int)), 1) - 2);
	else if(c == 's')
		return (ft_putstr_fd((va_arg(args, char *)), 1) - 2);
	else if(c == 'd' || c == 'i')
		return (ft_putnbase_fd(va_arg(args, int), 1, 10, 'x') - 2);
	else if(c == 'u')
		return (ft_putnbase_fd(va_arg(args, unsigned int), 1, 10, 'x') - 2);
	else if(c == 'x')
		return (ft_putnbase_fd(va_arg(args, unsigned int), 1, 16, 'x') - 2);
	else if(c == 'X')
		return (ft_putnbase_fd(va_arg(args, unsigned int), 1, 16, 'X') - 2);
	else if(c == 'p')
	{
		write(1, "0x", 2);
		return (ft_putnbase_fd(va_arg(args, unsigned long), 1, 16, 'x'));
	}
	return (0);
}

/* LIBFT */

size_t	ft_strlen(const char *src)
{
	size_t	index;

	index = 0;
	while (src && src[index])
	{
		index ++;
	}
	return (index);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (*s == '\0' && (char)c != *s)
			return (0);
		s++;
	}
	return ((char *) s);
}

int	ft_putchar_fd(char c, int fd)
{
		write(fd, &c, 1);
		return (1);
}

int	ft_putnbase_fd(long long nbr, int fd, int base, char x)
{
	int				len;

	if (base != 10)
		nbr = (unsigned long)nbr;
	len = putnbase_len(nbr, base);
	if (nbr < 0)
	{
		nbr = -nbr;
		ft_putchar_fd('-', fd);
	}
	if (nbr >= 0 && nbr <= 9)
		ft_putchar_fd((nbr + '0'), fd);
	else if ((base == 16) && (x == 'x') && (nbr >= 10 && nbr <= 15))
		ft_putchar_fd((nbr + 87), fd);
	else if ((base == 16) && (x == 'X') && (nbr >= 10 && nbr <= 15))
		ft_putchar_fd((nbr + 55), fd);
	else
	{
		ft_putnbase_fd((nbr / base), fd, base, x);
		ft_putnbase_fd((nbr % base), fd, base, x);
	}
	return (len);
}

static int	putnbase_len(long long n, int base)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		len ++;
		n = -n;
	}
	while (n > (base - 1))
	{
		n = n / base;
		len ++;
	}
	return (len);
}

int	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	len = 0;
	if (s == NULL)
	{
		write(fd, "(null)", 6);
		return (6);
	}
	len = ft_strlen(s);
	write(fd, s, len);
	return (len);
}

/* int	main(void)
{
	//int	t = -10000;
	//char str[] = "hello!";
	// ft_printf("\nreturn ft_printf:\t|%i|\n", ft_printf("'%%%'"));
	// printf("\nreturn printf:\t|%i|\n", printf("'%%%'"));
	//void *p;
	//ft_printf("\nreturn ft_printf:\t|%i|\n", ft_printf("%p", p));
	//printf("\nreturn printf:\t|%i|\n", printf("%p", p));

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
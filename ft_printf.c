/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joalmeid <joalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:10:15 by joalmeid          #+#    #+#             */
/*   Updated: 2022/06/23 16:13:23 by joalmeid         ###   ########.fr       */
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
int			ft_putnbr_fd(long n, int fd);
static int	putnubase_len(unsigned long n, unsigned long base);
static int	putnbr_len(long n);
int			ft_putnubase_fd(unsigned long nbr, int fd, int base, char type);

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
			ft_putchar_fd(src[index], 1);
	}
	va_end(args);
	printed += index;
	return (printed);
}

/* STATICS */

static int	print_arg(char c, va_list args)
{
	int	offset;

	offset = 2;
	if(c == '%')
		return (ft_putchar_fd('%', 1) - offset);
	else if(c == 'c')
		return (ft_putchar_fd((va_arg(args, int)), 1) - offset);
	else if(c == 's')
		return (ft_putstr_fd((va_arg(args, char *)), 1) - offset);
	else if(c == 'd' || c == 'i')
		return (ft_putnbr_fd(va_arg(args, int), 1) - offset);
	else if(c == 'u')
		return (ft_putnubase_fd(va_arg(args, unsigned int), 1, 10, 'x') - offset);
	else if(c == 'x')
		return (ft_putnubase_fd(va_arg(args, unsigned int), 1, 16, 'x') - offset);
	else if(c == 'X')
		return (ft_putnubase_fd(va_arg(args, unsigned int), 1, 16, 'X') - offset);
	else if(c == 'p')
	{
		write(1, "0x", 2);
		return (ft_putnubase_fd(va_arg(args, unsigned long), 1, 16, 'x'));
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

int	ft_putnbr_fd(long n, int fd)
{
	int	len;
	
	len = putnbr_len(n);
	if (n < 0)
	{
		n = -n;
		ft_putchar_fd('-', fd);
	}
	if (n >= 0 && n <= 9)
		ft_putchar_fd((n + '0'), fd);
	else
	{
		ft_putnbr_fd((n / 10), fd);
		ft_putnbr_fd((n % 10), fd);
	}
	return (len);
}

int	ft_putnubase_fd(unsigned long nbr, int fd, int base, char type)
{
	int	len;

	if (nbr >= 0 && nbr <= 9)
		ft_putchar_fd((nbr + 48), fd);
	else if ((base == 16) && (type == 'x') && (nbr >= 10 && nbr <= 15))
		ft_putchar_fd((nbr + 87), fd);
	else if ((base == 16) && (type == 'X') && (nbr >= 10 && nbr <= 15))
		ft_putchar_fd((nbr + 55), fd);
	else
	{
		ft_putnubase_fd((nbr / base), fd, base, type);
		ft_putnubase_fd((nbr % base), fd, base, type);
	}
	len = putnubase_len(nbr, base);
	return (len);
}

static int	putnubase_len(unsigned long n, unsigned long base)
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

/* #include <limits.h>
int	main(void)
{
	//int	t = -10000;
	//char str[] = "hello!";
	// ft_printf("\nreturn ft_printf:\t|%i|\n", ft_printf("'%%%'"));
	// printf("\nreturn printf:\t|%i|\n", printf("'%%%'"));
	//void *p;
	ft_printf("\nreturn ft_printf:\t|%i|\n\n", ft_printf("%p%p", ULONG_MAX, -ULONG_MAX));
	printf("\nreturn printf:\t|%i|\n", printf("%p%p", (long long *)ULONG_MAX, (long long *)-ULONG_MAX));

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
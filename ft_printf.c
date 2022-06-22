/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joalmeid <joalmeid@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:10:15 by joalmeid          #+#    #+#             */
/*   Updated: 2022/06/22 01:19:30 by joalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

size_t		ft_strlen(const char *src);
static int	print(const char *src, va_list params);
static int	print_param(char c, va_list params);

size_t	ft_strlen(const char *src);
char	*ft_strchr(const char *s, int c);
int	ft_putstr_fd(char *s, int fd);
int	ft_putchar_fd(char c, int fd);
int	ft_putnbase_fd(int n, int fd, int base, char x);

int	ft_printf(const char *src, ...)
{
	va_list	params;
	int		printed;

	if (!src)
		return (0);
	va_start(params, src);
	printed = print(src, params);
	va_end(params);
	return (printed);
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

int	ft_putnbase_fd(int n, int fd, int base, char x)
{
	long	nbr;
	int		len;

	nbr = n;
	len = 1;
	else if (nbr < 0)
	{
		nbr = -nbr;
		len += ft_putchar_fd('-', fd);
	}
	if (nbr >= 0 && nbr <= 9)
		len += ft_putchar_fd((nbr + '0'), fd);
	if ((base == 16) && x == 'x' && (nbr >= 10 && nbr <= 15))
		len += ft_putchar_fd((nbr + 87), fd);
	if ((base == 16) && x == 'X' && (nbr >= 10 && nbr <= 15))
		len += ft_putchar_fd((nbr + 55), fd);
	else
	{
		ft_putnbr_fd((nbr / base), fd, base, x);
		ft_putnbr_fd((nbr % base), fd, base, x);
	}
	return (len);
}

int	ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	index = 0;
	if (s == NULL)
		return ;
	len = ft_strlen(s);
	write(fd, s, len);
	return (len);
}

/* STATICS */

static int	print(const char *src, va_list params)
{
	int		index;
	int		printed;
	char	*reserved_c[10];
	int		removed;

	removed = 0;
	printed = 0;
	reserved_c = "cspdiuxX%";
	while (src[index])
	{
		if (src[index] == '%')
		{
			index ++;
			if (ft_strchr(reserved_c, src[index]))
			{
				printed += print_param(src[index], params);
				index ++;
				removed += 2;
			}
		}
		write(1, &src[i], 1);
		index ++;
	}
	printed += index - removed;
	return (printed);
}

/* • %c Prints a single character.
• %s Prints a string (as defined by the common C convention).
• %p The void * pointer argument has to be printed in hexadecimal format.
• %d Prints a decimal (base 10) number.
• %i Prints an integer in base 10.
• %u Prints an unsigned decimal (base 10) number.
• %x Prints a number in hexadecimal (base 16) lowercase format.
• %X Prints a number in hexadecimal (base 16) uppercase format.
• %% Prints a percent sign. */

static int	print_param(char c, va_list params)
{
	if(c == '%')
	{
		write(1, "%", 1);
		return (1);
	}
	if(c == 's')
		return (ft_putstr_fd(va_arg(params, char *), 1));
	if(c == 'p')
		return (ft_putnbase_fd(va_arg(params, int), 1, 16, 'x'));
	if(c == 'd' || c == 'i')
		return (ft_putnbase_fd(va_arg(params, int), 1, 10, 'x'));
	if(c == 'u')
		return (ft_putnbase_fd(va_arg(params, unsigned int), 1, 10, 'x'));
	if(c == 'x')
		return (ft_putnbase_fd(va_arg(params, int), 1, 16, 'x'));
	if(c == 'X')
		return (ft_putnbase_fd(va_arg(params, int), 1, 16, 'X'));
	return (0);
}

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

int	main(void)
{
	printf(" ");
}

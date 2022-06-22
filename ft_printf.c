/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joalmeid <joalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:10:15 by joalmeid          #+#    #+#             */
/*   Updated: 2022/06/22 17:52:38 by joalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

size_t		ft_strlen(const char *src);
static int	print(const char *src, va_list params);
static int	print_param(char c, va_list params);

size_t		ft_strlen(const char *src);
char		*ft_strchr(const char *s, int c);
int			ft_putstr_fd(char *s, int fd);
int			ft_putchar_fd(char c, int fd);
static int	putnbase_len(long n, int base);
int			ft_putnbase_fd(long nbr, int fd, int base, char x);
int			ft_putnbasep_fd(unsigned long *nbr, int fd, int base, char x);
void		*ft_calloc(size_t num, size_t size);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		ft_bzero(void *s, size_t n);

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

int	ft_putnbasep_fd(unsigned long *nbr, int fd, int base, char x)
{
	int		len;

	len = putnbase_len(*nbr, base);
	if (base == 16)
	{
		write(fd, "0", 1);
		write(fd, &x, 1);
	}
	if (*nbr < 0)
	{
		*nbr = -*nbr;
		ft_putchar_fd('-', fd);
	}
	if (*nbr >= 0 && *nbr <= 9)
		ft_putchar_fd((*nbr + '0'), fd);
	else if ((base == 16) && (x == 'x') && (*nbr >= 10 && *nbr <= 15))
		ft_putchar_fd((*nbr + 87), fd);
	else if ((base == 16) && (x == 'X') && (*nbr >= 10 && *nbr <= 15))
		ft_putchar_fd((*nbr + 55), fd);
	else
	{
		ft_putnbase_fd((*nbr / base), fd, base, x);
		ft_putnbase_fd((*nbr % base), fd, base, x);
	}
	return (len);
}

int	ft_putnbase_fd(long nbr, int fd, int base, char x)
{
	int		len;

	len = putnbase_len(nbr, base);
	if (base == 16)
	{
		write(fd, "0", 1);
		write(fd, &x, 1);
	}
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

static int	putnbase_len(long n, int base)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		len ++;
		n = -n;
	}
	else if (base == 16)
		len += 2;
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

void	*ft_calloc(size_t num, size_t size)
{
	void	*buffer;
	int		total;

	if (num == 0 || size == 0)
	{
		num = 1;
		size = 1;
	}
	total = num * size;
	buffer = malloc(total);
	if (buffer == NULL)
		return (NULL);
	ft_bzero(buffer, total);
	return (buffer);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char	*s;
	char		*d;

	s = src;
	d = dst;
	if (!s && !d && n > 0)
		return (NULL);
	while (n)
	{
		*d ++ = *s ++;
		n --;
	}
	return (dst);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*dst;

	dst = s;
	while (n > 0)
	{
		*dst = '\0';
		n --;
		dst ++;
	}
}

/* STATICS */

static int	print(const char *src, va_list params)
{
	int		index;
	int		printed;

	index = -1;
	printed = 0;
	while (src[++ index])
	{
		if (src[index] == '%')
		{
			index ++;
			if (ft_strchr("cspdiuxX%", src[index]))
			{
				printed += print_param(src[index], params);
			}
			if (!src[index])
				break ;
		}
		else
			write(1, &src[index], 1);
	}
	printed += index;
	return (printed);
}

/* • %c Prints a single character.
CHECK• %s Prints a string (as defined by the common C convention).
CHECK• %% Prints a percent sign. 
CHECK• %d Prints a decimal (base 10) number.
CHECK• %i Prints an integer in base 10.
CHECK• %u Prints an unsigned decimal (base 10) number.
• %p The void * pointer argument has to be printed in hexadecimal format.
• %x Prints a number in hexadecimal (base 16) lowercase format.
• %X Prints a number in hexadecimal (base 16) uppercase format.
*/

static int	print_param(char c, va_list params)
{
	if(c == '%')
	{
		write(1, "%", 1);
		return (- 1);
	}
	else if(c == 'c')
		return (ft_putchar_fd((va_arg(params, int)), 1) - 2);
	else if(c == 's')
		return (ft_putstr_fd((va_arg(params, char *)), 1) - 2);
	else if(c == 'd' || c == 'i')
		return (ft_putnbase_fd(va_arg(params, int), 1, 10, 'x') - 2);
	else if(c == 'u')
		return (ft_putnbase_fd(va_arg(params, unsigned int), 1, 10, 'x') - 2);
	else if(c == 'p')
		return (ft_putnbase_fd(va_arg(params, unsigned int), 1, 16, 'x') - 2);
	else if(c == 'x')
		return (ft_putnbase_fd(va_arg(params, unsigned int), 1, 16, 'x') - 2);
	else if(c == 'X')
		return (ft_putnbase_fd(va_arg(params, unsigned int), 1, 16, 'X') - 2);
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

/* int	main(void)
{
	//int	t = 10;
	//char str[] = "hello!";
	ft_printf("\nreturn printf:\t|%i|\n", ft_printf(" %%% "));
	//printf("%d", ft_printf("test%s", str));
} */

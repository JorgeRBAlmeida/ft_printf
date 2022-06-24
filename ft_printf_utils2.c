/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joalmeid <joalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 12:59:05 by joalmeid          #+#    #+#             */
/*   Updated: 2022/06/24 13:06:18 by joalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

int	ft_putstr_len(char *s, int fd)
{
	size_t	len;

	len = 0;
	if (s == NULL)
	{
		write(fd, "(null)", 6);
		return (6);
	}
	while (s[len])
	{
		len ++;
	}
	write(fd, s, len);
	return (len);
}

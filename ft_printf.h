/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joalmeid <joalmeid@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:13:32 by joalmeid          #+#    #+#             */
/*   Updated: 2022/06/24 09:22:49 by joalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_PRINTF_H
# define LIBFT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *src, ...);
size_t	ft_strlen(const char *src);
char	*ft_strchr(const char *s, int c);
int		ft_putstr_len(char *s, int fd);
int		ft_putchar_len(char c, int fd);
int		ft_putnbr_len(long n, int fd);
int		putnbr_len(long n);
int		ft_putnbase_u(unsigned long nbr, int fd, int base, char type);
int		putnbase_u_len(unsigned long n, unsigned long base);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joalmeid <joalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:13:32 by joalmeid          #+#    #+#             */
/*   Updated: 2022/06/24 13:01:24 by joalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *src, ...);

/* utils functions */

int		ft_putchar_len(char c, int fd);
int		ft_putnbr_len(long n, int fd);
int		ft_putnbase_u(unsigned long nbr, int fd, int base, char type);
char	*ft_strchr(const char *s, int c);
int		ft_putstr_len(char *s, int fd);

#endif
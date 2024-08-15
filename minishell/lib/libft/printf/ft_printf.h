/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:37:03 by vrandria          #+#    #+#             */
/*   Updated: 2024/08/15 16:42:34 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

int	ft_printf(const char *str, ...);
int	ft_putnbr(int nb);
int	ft_putnbr_u(long nb);
int	ft_putchar(char c);
int	ft_putstr(char *s);
int	ft_puthex_l(unsigned int nb);
int	ft_puthex_u(unsigned int nb);
int	ft_putnbr_unsigned(unsigned int nb);
int	ft_print_ptr(uintptr_t ptr);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:38:20 by vrandria          #+#    #+#             */
/*   Updated: 2024/08/15 16:42:31 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	ft_format(char str, va_list args)
{
	int	count;

	count = 0;
	if (str == 'c')
		count += ft_putchar((char) va_arg(args, int));
	else if (str == 's')
		count += ft_putstr((char *) va_arg(args, char *));
	else if (str == 'd' || str == 'i')
		count += ft_putnbr((int) va_arg(args, int));
	else if (str == 'u')
		count += ft_putnbr_unsigned((unsigned int) va_arg(args, unsigned int));
	else if (str == 'x')
		count += ft_puthex_l((unsigned int) va_arg(args, unsigned int));
	else if (str == 'X')
		count += ft_puthex_u((unsigned int) va_arg(args, unsigned int));
	else if (str == 'p')
		count += ft_print_ptr((uintptr_t) va_arg(args, uintptr_t));
	else if (str == '%')
		count += ft_putchar('%');
	return (count);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		count;
	va_list	args;

	i = 0;
	count = 0;
	va_start(args, str);
	while (str[i] != 0)
	{
		if (str[i] == '%')
		{
			i++;
			count += ft_format(str[i], args);
		}
		else
			count += ft_putchar(str[i]);
		i++;
		if (count < 0)
			return (-1);
	}
	va_end(args);
	return (count);
}

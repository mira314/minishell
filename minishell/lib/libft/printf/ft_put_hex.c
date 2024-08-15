/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:33:14 by vrandria          #+#    #+#             */
/*   Updated: 2024/03/07 10:33:23 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex_l(unsigned int nb)
{
	int		count;
	char	*hexadec;

	hexadec = "0123456789abcdefgh";
	count = 0;
	if (nb >= 16)
	{
		count += ft_puthex_l(nb / 16);
		count += ft_puthex_l(nb % 16);
	}
	else
	{
		count += ft_putchar(hexadec[nb]);
	}
	return (count);
}

int	ft_puthex_u(unsigned int nb)
{
	int		count;
	char	*hexadec;

	hexadec = "0123456789ABCDEFGH";
	count = 0;
	if (nb >= 16)
	{
		count += ft_puthex_u(nb / 16);
		count += ft_puthex_u(nb % 16);
	}
	else
	{
		count += ft_putchar(hexadec[nb]);
	}
	return (count);
}

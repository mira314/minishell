/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:20:28 by vrandria          #+#    #+#             */
/*   Updated: 2024/08/15 16:42:43 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int nb)
{
	char	c;
	int		i;

	i = 0;
	if (nb == -2147483648)
	{
		i += ft_putstr("-2147483648");
		return (i);
	}
	if (nb < 0)
	{
		i += ft_putchar('-');
		i += ft_putnbr(-nb);
	}
	if (nb > 9)
	{
		i += ft_putnbr(nb / 10);
		i += ft_putnbr(nb % 10);
	}
	if (nb >= 0 && nb < 10)
	{
		c = nb + 48;
		i += ft_putchar(c);
	}
	return (i);
}

int	ft_putnbr_unsigned(unsigned int nb)
{
	char			c;
	unsigned int	i;

	i = 0;
	if (nb > 9)
	{
		i += ft_putnbr(nb / 10);
		i += ft_putnbr(nb % 10);
	}
	if (nb < 10)
	{
		c = nb + 48;
		i += ft_putchar(c);
	}
	return (i);
}

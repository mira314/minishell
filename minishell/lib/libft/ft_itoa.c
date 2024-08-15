/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 14:31:39 by vrandria          #+#    #+#             */
/*   Updated: 2024/08/15 16:40:36 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		i;
	long	nb;

	nb = n;
	i = ft_numlen(nb);
	result = (char *)malloc((sizeof(char) * (i + 1)));
	if (!result)
		return (0);
	result[i] = 0;
	i--;
	if (nb == 0)
		result[i] = '0';
	if (nb < 0)
	{
		result[0] = '-';
		nb *= -1;
	}
	while (nb > 0)
	{
		result[i] = (nb % 10) + '0';
		nb = nb / 10;
		i--;
	}
	return (result);
}

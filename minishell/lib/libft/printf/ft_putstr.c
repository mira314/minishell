/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:43:21 by vrandria          #+#    #+#             */
/*   Updated: 2024/08/15 16:51:47 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *s)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (!s)
		return (ft_putstr("(null)"));
	while (s[i] != 0)
	{
		count += ft_putchar(s[i]);
		i++;
	}
	return (count);
}

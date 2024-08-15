/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:22:51 by vrandria          #+#    #+#             */
/*   Updated: 2024/08/15 16:33:55 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*result;

	result = dest;
	if (!dest && !src)
		return (0);
	while (n--)
	{
		*(char *)dest++ = *(char *)src++;
	}
	return (result);
}

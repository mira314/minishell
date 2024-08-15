/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 16:42:13 by vrandria          #+#    #+#             */
/*   Updated: 2024/08/15 16:42:17 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	li_len;
	size_t	i;

	i = 0;
	li_len = ft_strlen(little);
	if (*little == 0)
		return ((char *)big);
	while ((*big != 0) && (i < len))
	{
		if ((ft_strncmp(big, little, li_len) == 0) && (i + li_len <= len))
			return ((char *)big);
		big++;
		i++;
	}
	return (0);
}

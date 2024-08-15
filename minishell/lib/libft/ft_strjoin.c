/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 09:33:31 by vrandria          #+#    #+#             */
/*   Updated: 2024/08/15 16:40:23 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size;
	char	*result;
	size_t	len_s1;

	len_s1 = ft_strlen(s1);
	size = len_s1 + ft_strlen(s2);
	result = (char *)malloc(sizeof(char ) * (size + 1));
	if (!result)
		return (0);
	ft_strlcpy(result, s1, (len_s1 + 1));
	ft_strlcat(result, s2, (size + 1));
	return (result);
}

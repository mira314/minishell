/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 17:52:00 by vrandria          #+#    #+#             */
/*   Updated: 2024/08/15 16:41:11 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*beging;
	char	*ending;
	char	*result;

	if (!s1 || !set)
		return (0);
	beging = (char *)s1;
	ending = beging + ft_strlen(s1);
	while (*beging && ft_isset(*beging, set))
		beging++;
	while (beging < ending && ft_isset(*(ending - 1), set))
		ending--;
	result = ft_substr(beging, 0, (ending - beging));
	return (result);
}

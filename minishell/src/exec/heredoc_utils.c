/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 05:08:58 by derakoto          #+#    #+#             */
/*   Updated: 2024/12/17 12:08:58 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_delimiter(char *delimiter, char *str)
{
	size_t	i;
	size_t	len;

	if (delimiter == NULL && str == NULL)
		return (0);
	if (delimiter == NULL || str == NULL)
		return (1);
	len = ft_strlen(str);
	if (len != ft_strlen(delimiter))
		return (1);
	i = 0;
	while (i < len)
	{
		if (delimiter[i] != str[i])
			return (1);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 07:45:53 by derakoto          #+#    #+#             */
/*   Updated: 2024/12/18 07:49:54 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	count_quote_to_protect(char *str)
{
	int	quote_count;
	int	i;

	quote_count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
			quote_count++;
		i++;
	}
	return (quote_count);
}

char	*protect_quote(char *str)
{
	char	*result;
	int		i;
	int		quote_count;
	int		j;

	if (str == NULL)
		return (str);
	i = 0;
	quote_count = count_quote_to_protect(str);
	result = (char *)malloc(sizeof(char) * (quote_count + ft_strlen(str) + 1));
	if (result == NULL)
		return (str);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
			result[j++] = 14;
		result[j++] = str[i++];
	}
	result[j] = '\0';
	free(str);
	return (result);
}

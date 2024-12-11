/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 05:54:57 by derakoto          #+#    #+#             */
/*   Updated: 2024/12/11 12:53:58 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	mini_tbl_len(char **tbl)
{
	int	i;

	i = 0;
	while (tbl[i] != 0)
		i++;
	return (i);
}

void	mini_tbl_free(char **tbl)
{
	int	i;

	if (tbl == 0)
		return ;
	i = 0;
	while (tbl[i] != 0)
	{
		free(tbl[i]);
		i++;
	}
	free(tbl[i]);
	free(tbl);
}

int	in_long_range(char *str)
{
	int		result;
	size_t	i;

	result = 0;
	if (str == NULL)
		return (-1);
	str = ft_strtrim(str, " ");
	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i = 1;
	if (ft_strlen(str) > 19 + i)
		result = 1;
	else if (ft_strlen(str) < 19 + i)
		result = 0;
	else if (i && ((str[0] == '+' && ft_strcmp(str + 1, LONG_MAX_STR) > 0)
			|| (str[0] == '-' && ft_strcmp(str + 1, LONG_MIN_STR) > 0)))
		result = 1;
	else if (ft_strcmp(str, LONG_MAX_STR) > 0)
		result = 1;
	else
		result = 0;
	free(str);
	return (result);
}

int	mini_is_numeric(char *str)
{
	size_t	i;

	if (str == NULL)
		return (-1);
	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == 0)
		return (-1);
	if (str[i] == '+' || str[i] == '-')
	{
		if (!ft_isdigit(str[i + 1]))
			return (-1);
		i++;
	}
	while (ft_isdigit(str[i]))
		i++;
	while (str[i] == ' ')
		i++;
	if (str[i] != 0)
		return (-1);
	return (0);
}

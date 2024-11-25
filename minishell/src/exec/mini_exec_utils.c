/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 05:54:57 by derakoto          #+#    #+#             */
/*   Updated: 2024/11/25 05:55:45 by derakoto         ###   ########.fr       */
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

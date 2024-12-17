/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_up_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 07:35:15 by derakoto          #+#    #+#             */
/*   Updated: 2024/12/17 12:17:11 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	load_history(int fd_history)
{
	char	*str;

	str = get_next_line(fd_history);
	while (str != NULL)
	{
		str[ft_strlen(str) - 1] = '\0';
		add_history(str);
		free(str);
		str = get_next_line(fd_history);
	}
}

t_data	*static_data(t_data *data)
{
	static t_data	*data_stat = NULL;

	if (data != NULL)
	{
		data_stat = data;
		return (NULL);
	}
	return (data_stat);
}

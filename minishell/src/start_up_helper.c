/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_up_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 07:35:15 by derakoto          #+#    #+#             */
/*   Updated: 2024/12/17 09:24:15 by vrandria         ###   ########.fr       */
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

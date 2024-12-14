/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_up_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 07:35:15 by derakoto          #+#    #+#             */
/*   Updated: 2024/12/14 08:02:26 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	load_history(int fd_history)
{
	char	*str;

	str = get_next_line(fd_history);
	while (str != NULL)
	{
		add_history(str);
		free(str);
		str = get_next_line(fd_history);
	}
}

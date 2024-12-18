/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 09:45:09 by derakoto          #+#    #+#             */
/*   Updated: 2024/12/18 10:29:52 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int_handler(int sig_num)
{
	(void)sig_num;
	g_last_val = 130;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay ();
}

void	child_sigint_handler(int sig_num)
{
	t_data	*data;

	(void) sig_num;
	data = static_data(NULL);
	free_and_exit(data, 130);
}

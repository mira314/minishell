/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 09:45:09 by derakoto          #+#    #+#             */
/*   Updated: 2024/10/21 07:12:00 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    sig_int_handler(int sig_num)
{
    (void)sig_num;
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay ();
}
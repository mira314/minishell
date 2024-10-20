/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 05:19:02 by derakoto          #+#    #+#             */
/*   Updated: 2024/10/20 11:57:43 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void    mini_exit(t_data *data)
{
    mini_tbl_free(data->env);
    printf("exit\n");
    if (mini_tbl_len(data->cmd->args) > 2)
    {
        ft_putstr_fd("exit: too many arguments\n", 2);
        exit(1);
    }
    exit(0);
}
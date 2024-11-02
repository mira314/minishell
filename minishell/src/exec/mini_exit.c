/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 05:19:02 by derakoto          #+#    #+#             */
/*   Updated: 2024/11/02 11:40:16 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void    mini_exit(t_data *data)
{
    mini_tbl_free(data->env);
    mini_tbl_free(data->var);
    printf("exit\n");
    if (data->cmd == NULL)
        exit(0);
    if (mini_tbl_len(data->cmd->args) > 2)
    {
        ft_putstr_fd("exit: too many arguments\n", 2);
        exit(1);
    }
    if (mini_tbl_len(data->cmd->args) == 2)
    {
        if (mini_is_numeric(data->cmd->args[1]) != 0)
        {
            ft_putstr_fd("exit: ", 2);
            ft_putstr_fd(data->cmd->args[1], 2);
            ft_putstr_fd(": Argument should be numeric\n", 2);
            exit(2);
        }
        exit(ft_atoi(data->cmd->args[1]));
    }
    exit(0);
}

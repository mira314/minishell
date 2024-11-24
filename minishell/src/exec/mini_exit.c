/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 05:19:02 by derakoto          #+#    #+#             */
/*   Updated: 2024/11/24 13:53:25 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void free_and_exit(t_data *data, int exit_code)
{
    mini_tbl_free(data->env);
    mini_tbl_free(data->var);
    clear_lst_cmd(data);
    exit(exit_code);
}

void    mini_exit(t_data *data, t_cmd *cmd)
{
    char    **args;
    int     arg_len;

    printf("exit\n");
    if (data->input != NULL)
    {
        args = cmd->args + cmd->offset;
        arg_len = mini_tbl_len(args);
        if (arg_len >= 2)
        {
            if (mini_is_numeric(args[1]) != 0)
            {
                ft_putstr_fd("exit: ", 2);
                ft_putstr_fd(args[1], 2);
                ft_putstr_fd(": Argument should be numeric\n", 2);
                free_and_exit(data, 2);
            }
            else if (arg_len == 2)
                free_and_exit(data, ft_atoi(args[1]));
            ft_putstr_fd("exit: too many arguments\n", 2);
            free_and_exit(data, 1);
        }
    }
    free_and_exit(data, 0);
}



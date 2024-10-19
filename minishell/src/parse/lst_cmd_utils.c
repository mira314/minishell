/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 07:51:18 by vrandria          #+#    #+#             */
/*   Updated: 2024/10/19 10:55:44 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_cmd *new_cmd(void)
{
    t_cmd *new;

    new = (t_cmd *)malloc(sizeof(t_cmd));
    if (!new)
        return (0);
    new = init_cmd(new);
    return (new);
}

t_cmd *lst_add_back_cmd(t_cmd *cmd, t_cmd *new_cmd)
{
    t_cmd *tmp;

    tmp = cmd;

    if (tmp == 0)
    {
        cmd = new_cmd;
        return(cmd);
    }
    if (tmp && new_cmd)
    {
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_cmd;
        new_cmd->prev = tmp;
    }
    return(cmd);
}
static t_cmd *lst_del_cmd(t_cmd *cmd)
{
    t_cmd *tmp;

    tmp = cmd->next;
    free(cmd->cmd);
    free(cmd->history);
    cmd->history = 0;
    free(cmd->args);
    cmd->args = 0;
    cmd->cmd = 0;
    return (tmp);
}

void clear_lst_cmd(t_data *data)
{
    t_cmd *cmd;

    cmd = data->cmd;
    while (cmd)
        cmd = lst_del_cmd(cmd);
    data->cmd = 0;
}
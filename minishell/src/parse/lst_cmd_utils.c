/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 07:51:18 by vrandria          #+#    #+#             */
/*   Updated: 2024/10/19 14:55:21 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_cmd *new_cmd(void)
{
    t_cmd *new;
    t_cmd *tmp;

    new = (t_cmd *)malloc(sizeof(t_cmd));
    if (!new)
        return (0);
    tmp = init_cmd(new);
    if (!tmp)
    {
        free(new);
        return (0);
    }
    return (tmp);
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
    t_cmd *current = cmd;
    int i;

    i = 0;
    while (current)
    {
        t_cmd *next_cmd = current->next;

        if (current->args)
        {
            while (current->args[i])
            {
                free(current->args[i]);
                i++;
            }
        }
        free(current->args);
        free(current->cmd);
        free(current->history);
        free(current);
        current = next_cmd; 
    }

    return NULL;
}


void clear_lst_cmd(t_data *data)
{
    if (data->cmd != 0)
    {
        lst_del_cmd(data->cmd);
        data->cmd = NULL;
    }
}



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 07:51:18 by vrandria          #+#    #+#             */
/*   Updated: 2024/11/19 05:09:07 by derakoto         ###   ########.fr       */
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

void clear_inputs(t_input *input)
{
    int i;

    if (input == 0)
        return ;
    i = 0;
    while (input[i].filename != NULL)
    {
        free(input[i].filename);
        i++;
    }
}

void clear_outputs(t_output *output)
{
    int i;

    if (output == NULL)
        return ;
    i = 0;
    while (output[i].filename != NULL)
    {
        free(output[i].filename);
        i++;
    }
}
void clear_io(t_io_fd *io)
{
    if (io == NULL)
        return ;
    clear_inputs(io->inputs);
    free(io->inputs);
    clear_outputs(io->outputs);
    free(io->outputs);
}

static t_cmd *lst_del_cmd(t_cmd *cmd)
{
    t_cmd *current = cmd;
    t_cmd *next_cmd;

    while (current)
    {
        next_cmd = current->next;
        mini_tbl_free(current->args);
        free(current->cmd);
        clear_io(current->io);
		free(current->io);
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



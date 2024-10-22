/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 08:24:27 by vrandria          #+#    #+#             */
/*   Updated: 2024/10/19 09:05:23 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void clear_lst_file(t_file *file)
{
    t_file *cur;

    if (file)
    {
        while (file)
            {
                cur = file;
                free(file->file);
                file = file->next;
                free(cur);
            }
    }
}

t_file *lst_new_file(t_file *io, char *str)
{
    t_file *new;
    t_file *cur;

    cur = io;
    new = malloc(sizeof(t_file));
    if (!new)
        return (0);
    new->file = ft_strdup(str);
    if (new->file == 0)
        return (0);
    while (io->next)
        io = io->next;
    new->next = new;
    return (cur);
}
/*
int files_operation(t_io_fd *in_outm int files)
{

    
}
int acces_file(t_io_fd *in_out, char *name, char *files)
{
    
    return (1);
}
*/

t_token *parsing_input(t_cmd *cmd, t_token *token)
{
    (void)token;
    while (cmd)
        cmd = cmd->next;
    init_input_output(cmd);
    return (0);
}
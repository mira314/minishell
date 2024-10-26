/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 08:24:27 by vrandria          #+#    #+#             */
/*   Updated: 2024/10/26 10:01:47 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"



int files_operation(t_io_fd *in_out, int files)
{
    if (files == 1 && in_out->inputs)
    {
        if (in_out->input_fd == -1 || (in_out->outputs && in_out->output_fd == -1)) // ajoute de mode plus tard
            return (0);
        if (in_out->delim_heredoc != NULL)
        {
            free(in_out->delim_heredoc);
            unlink(in_out->inputs);
        }
        free(in_out->inputs);
        close(in_out->input_fd);
    }
    else if (files == 0 && in_out->outputs)
    {
        if (in_out->output_fd == -1 || (in_out->inputs && in_out->input_fd == -1))
            return (0);
        free(in_out->outputs);
        close(in_out->output_fd);
    }
    return (1);

    
}
int acces_file(t_io_fd *in_out, char *name, char *files)
{
    if (files_operation(in_out, 1) == 0)
        return (0);
    in_out->inputs = ft_strdup(name);
    if (in_out->inputs && in_out->inputs[0] == 0)
    {
        print_error(files, "ambiguous redirect",1);
        return (0);
    }
    in_out->input_fd = open(in_out->inputs, O_RDONLY);
    if (in_out->input_fd == -1)
    {
        print_error(files, "ambiguous redirect",1);
        free(in_out->inputs);
    }
    return (1);
}


t_token *parsing_input(t_cmd *cmd, t_token *token)
{
    while (cmd->next)
        cmd = cmd->next;
    init_input_output(cmd);
    acces_file(cmd->io, token->next->str, token->next->temp);
    if (token->next->next)
        token = token->next->next;
    else
        token = token->next;
    return (token);
}
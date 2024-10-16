/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_proces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 11:07:54 by vrandria          #+#    #+#             */
/*   Updated: 2024/10/16 08:59:38 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"parse.h"

t_token *parsing_pipe(t_data *data, t_token *token)
{
    t_cmd *cmd;

    cmd = data->cmd;
    while (cmd->next)
        cmd = cmd->next;
    cmd->output =  1;
    cmd = lst_add_back_cmd(cmd, new_cmd());
    token =  token->next;
    return (token);
}
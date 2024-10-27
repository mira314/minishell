/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trunc_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:44:56 by vrandria          #+#    #+#             */
/*   Updated: 2024/10/27 11:07:02 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void create_file(t_cmd *cmd, t_token *token)
{
    cmd->io->outputs[0].filename = ft_strdup(token->str);
    cmd->io->outputs[0].mode = TRUNC;
}

static t_output *add_file(t_cmd *cmd, t_token *token)
{
    int i;
    int count;
    t_output *tmp;
    t_output *new;

    i = 0;
    count = 0;
    tmp = cmd->io->outputs;
    while (tmp[i].filename)
        i++;
    new = malloc((sizeof(t_output) * (i + 2)));
    if (!new)
        return (0);
    while (count < i)
    {
        new[count].filename = ft_strdup(tmp[count].filename);
        free(tmp[count].filename);
        new[count].mode = tmp[count].mode;
        count++;
    }
        new[count].filename = ft_strdup(token->str);
        new[count].mode = TRUNC;
        new[count + 1].filename = 0;
    return (new);
}

t_token *parsing_trunc(t_cmd *cmd, t_token *token)
{
    t_output *tmp;

    tmp = cmd->io->outputs;
    while (cmd->next)
        cmd = cmd->next;
    if (cmd->io->outputs[0].filename == 0)
        create_file(cmd, token->next);
    else
        {
            cmd->io->outputs = add_file(cmd, token->next);
            free(tmp);
        }
    if (token->next->next)
    {
        token = token->next->next;
    }
    else
        token = token->next;
    return (token);
}
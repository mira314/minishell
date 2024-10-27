/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:42:25 by vrandria          #+#    #+#             */
/*   Updated: 2024/10/27 12:02:35 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void create_file(t_cmd *cmd, t_token *token)
{
    cmd->io->inputs[0].filename = ft_strdup(token->temp);
    cmd->io->inputs[0].mode = HEREDOC;
}

static t_input *add_file(t_cmd *cmd, t_token *token)
{
    int i;
    int count;
    t_input *tmp;
    t_input *new;

    i = 0;
    count = 0;
    tmp = cmd->io->inputs;
    while (tmp[i].filename)
        i++;
    new = malloc((sizeof(t_input) * (i + 2)));
    if (!new)
        return (0);
    while (count < i)
    {
        new[count].filename = ft_strdup(tmp[count].filename);
        free(tmp[count].filename);
        new[count].mode = tmp[count].mode;
        count++;
    }
        new[count].filename = ft_strdup(token->temp);
        new[count].mode = HEREDOC;
        new[count + 1].filename = 0;
    return (new);
}

t_token *parsing_heredoc(t_cmd *cmd, t_token *token)
{
    t_input *tmp;

    tmp = cmd->io->inputs;
    while (cmd->next)
        cmd = cmd->next;
    if (cmd->io->inputs[0].filename == 0)
        create_file(cmd, token->next);
    else
        {
            cmd->io->inputs = add_file(cmd, token->next);
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 07:31:00 by vrandria          #+#    #+#             */
/*   Updated: 2024/09/18 08:11:26 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int init_data(t_data *data)
{
    data->input = 0;
    data->cmd = 0;
    data->token = 0;
    data->exit_value = 1;
    return (1);
}

int init_token(t_data *data, char *input, int flag)
{
    int i;
    int start;
    int limit;

    i = 0;
    start = 0;
    limit = ft_strlen(input);
    while (limit >= i)
    {
        flag = check_quote(flag, (int)input[i]);
        if (flag == EMPTY)
            start = token_split_word_and_sep(input, start, data, &i);
        //printf("start = %d, i = %d\n", start, i);
        i++;
    }
    if (flag != EMPTY)
    {
        if (flag == DOUBLE_QUOTE || flag == ONE_QUOTE)
        {
            printf("unexpected quote is not close\n");
            return(1);
        }
    }
    return (0);
}

t_cmd *init_cmd(t_cmd *cmd)
{
    cmd->cmd = 0;
    cmd->args = 0;
    cmd->output = 0;
    cmd->prev = 0;
    cmd->next = 0;
    cmd->history = 0;
    return (cmd);
}

void fill_cmd(t_data *data, t_token *token)
{
    t_token *tmp;

    tmp = token;
    if (tmp->type_token == END)
        return ;
    while (tmp->next)
    {
        if (tmp == token)
            data->cmd = lst_add_back_cmd(data->cmd, new_cmd());
        if (tmp->type_token == WORD || tmp->type_token == VAR)
            tmp = parsins_word(data->cmd, tmp);
        else if (token->type_token == END)
            break ;
    }
    if (data && data->cmd)
        data->exit_value = parse_commande(data);
    else
        data->exit_value = 1;
}
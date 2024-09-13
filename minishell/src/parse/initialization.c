/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 07:31:00 by vrandria          #+#    #+#             */
/*   Updated: 2024/09/13 13:06:20 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int init_data(t_data *data)
{
    data->input = 0;
    data->cmd = 0;
    data->token = 0;
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
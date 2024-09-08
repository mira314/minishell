/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 07:35:00 by vrandria          #+#    #+#             */
/*   Updated: 2024/08/31 15:46:25 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int check_quote(int flag, int input)
{
    if (input == 39 && flag == NO_QUOTE)
        flag = ONE_QUOTE;
    else if (input == 34 && flag == NO_QUOTE)
        flag = DOUBLE_QUOTE;
    else if (input == 39 && flag == ONE_QUOTE)
        flag = NO_QUOTE;
    else if (input == 34 && flag == DOUBLE_QUOTE)
        flag = NO_QUOTE;
    return (flag);
}

/**flag is for to check is quote inthe str*/

int init_token(t_data *data, char *input, int flag)
{
    int i;
    //int start;
    int limit;

    (void)data;
    i = 0;
    //start = 0;
    limit = ft_strlen(input);
    while (limit >= i)
    {
        flag = check_quote(flag, (int)input[i]);
        /*
        if (flag == NO_QUOTE)
        {
            return (0); // a ajouter dans t_cmd
        }
        */
        i++;
    }
    if (flag != NO_QUOTE)
    {
        if (flag == DOUBLE_QUOTE || flag == ONE_QUOTE)
        {
            printf("quote is not close\n");
            return(1);
        }
    }
    return (0);
}


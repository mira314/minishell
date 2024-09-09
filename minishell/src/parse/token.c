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
    if (input == 39 && flag == EMPTY)
        flag = ONE_QUOTE;
    else if (input == 34 && flag == EMPTY)
        flag = DOUBLE_QUOTE;
    else if (input == 39 && flag == ONE_QUOTE)
        flag = EMPTY;
    else if (input == 34 && flag == DOUBLE_QUOTE)
        flag = EMPTY;
    return (flag);
}

int what_is_sep(char *str, int i)
{
    if (str[i] >= 9 && str[i] <= 13)
        return (SPACES);
    if (str[i] == 32)
        return (SPACES);
    if (str[i] == '<' && str[i + 1] != '<')
        return (INPUT);
    if (str[i] == '>' && str[i + 1] != '>')
        return (TRUNC);
    if (str[i] == '<' && str[i + 1] == '<')
        return (HEREDOC);
    if (str[i] == '>' && str[i + 1] == '>')
        return (APPEND);
    if (str[i] == 0)
        return (END);
    if (str[i] == '|')
        return (PIPE);
    return (0);
}

int token_split_word_and_sep(char *str, int start, t_data *data, int i)
{
    int token_type;
    (void)data;
    (void)start;

    token_type = what_is_sep(str, i);
    if (token_type)
    {
        if (i != 0 && (!what_is_sep(str, i - 1)))
            printf("is_word");
        if (token_type == HEREDOC || token_type == PIPE || token_type == APPEND || token_type == END || token_type == TRUNC || token_type == INPUT)
        {
            printf("token is %d", token_type);
            if (token_type == HEREDOC || token_type == APPEND)
                i++;
        }
    }
    return (i);

}
/**flag is for to check is quote inthe str*/

int init_token(t_data *data, char *input, int flag)
{
    int i;
    int start;
    int limit;

    (void)data;
    i = 0;
    start = 0;
    limit = ft_strlen(input);
    while (limit >= i)
    {
        flag = check_quote(flag, (int)input[i]);
        if (flag == EMPTY)
        {
            i = token_split_word_and_sep(input, start, data, i);
            printf("ici i = %d\n",i );
        }
        i++;
        start = i;
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


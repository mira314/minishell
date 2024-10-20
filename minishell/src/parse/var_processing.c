/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 08:54:14 by vrandria          #+#    #+#             */
/*   Updated: 2024/10/19 14:40:01 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_token *statu_quote_token(t_token *token, int c)
{
    if (c == 39 && token->flag == EMPTY)
        token->flag =  ONE_QUOTE;
    else if (c == 34 && token->flag == EMPTY)
        token->flag = DOUBLE_QUOTE;
    else if (c == 39 && token->flag == ONE_QUOTE)
        token->flag = EMPTY;
    else if (c == 34 && token->flag == DOUBLE_QUOTE)
        token->flag = EMPTY;
    return (token);
}

int sep_next_char(char c)
{
    if (c == '$')
        return (1);
    else if (c == 32)
        return (1);
    else if (c == 0)
        return (1);
    return (0);
}

int double_quote_is_close(char *str, int i)
{
    int prev;
    int next;
    int len;

    prev = i - 1;
    next = i + 1;
    len = ft_strlen(&str[i]);
    if (prev >= 0 && len > 0)
    {
        if (str[prev] == 34 && str[next] == 34)
            return (1);
    }
    return (0);

}

int var_process(t_data *data, t_token *token)
{
    int i;
    char *exit_val;
    char *tmp;
    char *cur;

    while (token)
    {
        if (token->type_token == VAR)
        {
            i = 0;
            while (token->str[i])
            {
                token = statu_quote_token(token, (int)(token->str[i]));
                if (token->str[i] == '$' && double_quote_is_close(token->str, i) == 0 && sep_next_char(token->str[i + 1] == 0)
                && (token->flag == EMPTY || token->flag == DOUBLE_QUOTE))//il le faut dans une fonctionne
                {
                    tmp = token->str;
                    if (token->str[0] == '$' && token->str[1] == '+')
                    {
                        cur = ft_strjoin("$", token->str);
                        free(token->str);
                        token->str = cur;
                    }
                    exit_val = exit_var_value(data, token, &tmp[i]);
                    token = var_conversion(token, exit_val, i);
                    i++;
                }
                else
                    i++;
            }
        }
        token = token->next;
    }
    return (SUCCESS);
}
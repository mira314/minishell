/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_proces_utils_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 10:54:54 by vrandria          #+#    #+#             */
/*   Updated: 2024/10/13 10:57:45 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int sub_var(t_token *token, char *str, int i, int size)
{
    int j;
    int y;
    char *new;

    j = 0;
    y = 0;

    size = size - size_var(&str[i]);
    new = (char *)malloc(sizeof(char) + size + 1);
    if (!new)
        return (0);
    while (str[j])
    {
        if (str[j] == '$' && i == j)
        {
            j = size_var(&str[i]) + j + 1;
            if (str[j] == 0)
                break ;
        }
        new[y] = str[j];
        y++;
        j++;
    }
    new[y] = 0;
    free(token->str);
    token->str = 0;
    token->str = new;
    return (0);
}

t_token *var_conversion(t_token *token, char *str, int i)
{
    int size;

    size = ft_strlen(token->str);
    if (str == 0)
        sub_var(token, token->str, i,  size);
    else
        sub_var_replace(token, token->str, str, i);
   return (token);
}

int var_copy(char *dest, char *src, int i)
{
    int j;

    j = 0;
    while (src[j])
    {
        dest[i] = src[j];
        j++;
        i++;
    }
    return (i);
}

char *get_str_token(char *str, char *str_new, int size, int i)
{
    char *str_token;
    int j;
    int y;

    j = 0;
    y = 0;
    str_token = (char *)malloc(sizeof(char) * size + 1);
    if (!str_token)
        return (0);
    while (str[j])
    {
        if (str[j] == '$' && j == i)
        {
            y = var_copy(str_token, str_new, y);
            j = size_var(&str[i]) + j + 1;
            if (str[j] == 0)
                break ;
        }
        str_token[y] = str[j];
        j++;
        y++;
    }
    str_token[y] = 0;
    return(str_token);
}
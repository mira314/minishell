/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_proces_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:41:39 by vrandria          #+#    #+#             */
/*   Updated: 2024/10/12 10:25:05 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int is_correct_type_var(char c)
{
    if (c == '_')
        return (1);
    else if (ft_isalpha(c))
        return (1);
    else if (ft_isdigit(c))
        return (1);
    else
        return (0);
}

int size_var(char *var)
{
    int i;
    int size;

    i = 0;
    size = 0;
    while (var[i] != '$')
        i++;
    if (var[i + 1] == '?' || ft_isdigit(var[i + 1]) == 1)
        return (1);
    i = 1;
    while (var[i])
    {
        if (is_correct_type_var(var[i]) == 0)
            return (size);
        size++;
        i++;
    }
    return (size);

}
char *get_type_var(char *var, int start)
{
    char *str;
    int i;
    int size;
    char *var_env;

    i = 0;
    while (var[i])
    {
        if (var[i] == '$')
        {
            start = i + 1;
            break ;
        }
        i++;
    }
    size = size_var(var);
    str = ft_substr(var, start, size);
    if (!str)
        return (0);
    var_env = (char *)malloc(sizeof(char) * ft_strlen(str) + 2);
    ft_strlcpy(var_env, str, ft_strlen(str) + 1);
    var_env[ft_strlen(str)] = '=';
    var_env[ft_strlen(str) + 1] = 0;
    free(str);
    return (var_env);
}

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

int sub_var_replace(t_token *token, char *str_new, char *str, int i)
{
    char *new;
    int size;
    int len_var;
    len_var = size_var(&str_new[i]);
    size = ft_strlen(str) -  len_var + ft_strlen(str_new);
    new = get_str_token(str, str_new, size, i);
    if (token)
    {
        free(token->str);
        token->str = new;
    }

    return (1);
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
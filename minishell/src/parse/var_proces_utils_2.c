/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_proces_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:41:39 by vrandria          #+#    #+#             */
/*   Updated: 2024/10/13 10:57:56 by vrandria         ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_proces_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:41:39 by vrandria          #+#    #+#             */
/*   Updated: 2024/09/29 15:45:24 by vrandria         ###   ########.fr       */
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
    i++;
    while (var[i])
    {
        if (is_correct_type_var(var[i]) == 0)
            return (size);
        else
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

    i = 0;
    while (var[i])
    {
        if (var[i] == '$')
        {
            start = i + 1;
            break ;
        }
        else
            i++;
    }
    size = size_var(var);
    str = ft_substr(var, start, size);
    if (!str)
        return (0);
    free(var);
    return (str);
}
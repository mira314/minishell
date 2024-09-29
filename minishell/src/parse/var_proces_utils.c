/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_proces_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 09:11:02 by vrandria          #+#    #+#             */
/*   Updated: 2024/09/28 09:37:30 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"


int ft_varchr(t_data *data, char *str)
{
    int i;
    int size;

    i = 0;
    size = ft_strlen(str);
    while (data->env[i])
    {
        if (ft_strncmp(data->env[i], str , size) == 0)
            return (1);
        i++;
    }
    return (0);
}

char *get_var_env(t_data *data, char *str, int size)
{
    char *result;
    int i;

    i = 0;
    while (data->env[i])
    {
        if (ft_strncmp(data->env[i], str, size) == 0)
            break ;
        else
            i++;
    }
    result = ft_strdup(data->env[i]);
    result = &result[size + 1];
    return (result);
}

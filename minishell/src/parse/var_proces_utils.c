/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_proces_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 09:11:02 by vrandria          #+#    #+#             */
/*   Updated: 2024/10/12 10:28:03 by vrandria         ###   ########.fr       */
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

char *get_var_env(t_data *data, char *str, int size_var)
{
    char *result;
    int i;

    i = 0;
    while (data->env[i])
    {
        if (ft_strncmp(data->env[i], str, size_var) == 0)
            break ;
        else
            i++;
    }
    result = ft_strdup(data->env[i]);
    result = &result[size_var];
    return (result);
}

char *exit_var_value(t_data *data, t_token *token, char *str)
{
    char *exit_val;
    char *var;
    int size;

    var = get_type_var(str, 0);
    if (var && ft_varchr(data, var) == 1)
    {
        if (token)
            token->check_var = 1;
        size = ft_strlen(var);
        exit_val = get_var_env(data, var, size);
    }
    else if (var && var[0] == '?' && var[1] == '=')
        exit_val =  ft_itoa(g_last_val);
    else
        exit_val = 0;
    free(var);
    return (exit_val);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_proces_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 09:11:02 by vrandria          #+#    #+#             */
/*   Updated: 2024/11/24 11:56:13 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int ft_varchr(t_data *data, char *str)
{
    int i;
    int size;

    i = 0;
    size = ft_strlen(str);
    while (data->var[i])
    {
        if (ft_strncmp(data->var[i], str , size) == 0)
            return (1);
        i++;
    }     
    i = 0;
    while (data->env[i])
    {
        if (ft_strncmp(data->env[i], str , size) == 0)
            return (2);
        i++;
    }
    return (0);
}

char *get_var_var(t_data *data, char *str, int size_var)
{
    char *result;
    int i;
    char *sub;

    i = 0;
    while (data->var[i])
    {
        if (ft_strncmp(data->var[i], str, size_var) == 0)
            break ;
        else
            i++;
    }
    result = ft_strdup(data->var[i]);
    sub = ft_substr(result, size_var, ft_strlen(result));
    free(result);
    return (sub);
}

char *get_var_env(t_data *data, char *str, int size_var)
{
    char *result;
    int i;
    char *sub;

    i = 0;
    while (data->env[i])
    {
        if (ft_strncmp(data->env[i], str, size_var) == 0)
            break ;
        else
            i++;
    }
    result = ft_strdup(data->env[i]);
    sub = ft_substr(result, size_var, ft_strlen(result));
    free(result);
    return (sub);
}

char *exit_var_value(t_data *data, t_token *token, char *str)
{
    char *exit_val;
    char *var;
    int size;

    var = get_type_var(str, 0);
    if (var && ft_varchr(data, var) != 0)
    {
        if (token)
            token->check_var = 1;
        size = ft_strlen(var);
        if (ft_varchr(data, var) == 1)
            exit_val = get_var_var(data, var, size);
        else if (ft_varchr(data, var) == 2)
            exit_val = get_var_env(data, var, size);
    }
    else if (var && var[0] == '?' && var[1] == '=')
        exit_val =  ft_itoa(data->exit_value);
    else
        exit_val = 0;
    free(var);
    return (exit_val);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 10:34:21 by derakoto          #+#    #+#             */
/*   Updated: 2023/11/22 00:41:30 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int is_var_assignement(char *str)
{
    int i;

    if (str == NULL)
        return (-1);
    i = 0;
    if (str[0] == '=')
        return (-1);
    while (ft_isalnum(str[i]) && str[i] != 0)
        i++;
    if (str[i] != '=')
        return (-1);
    return (0);
}

int count_assignement(char **tbl)
{
    int i;
    int result;

    if (tbl == NULL)
        return (-1);
    i = 0;
    result = 0;
    while (tbl[i] != NULL)
    {
        if (is_var_assignement(tbl[i]) == 0)
                result++ ;
        i++;
    }
    return (result);
}

int handle_var(char **tbl, char ***var, int *assign_count)
{
    *assign_count = count_assignement(tbl);
    if (*assign_count == -1)
        return (FAIL);
    if (tbl[*assign_count] == NULL)
    {
        printf("Execute assignement\n");
        *var = add_env(*var, tbl);
        return (SUCCESS);
    }
    return (FAIL);
}
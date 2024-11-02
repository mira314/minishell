/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 10:34:21 by derakoto          #+#    #+#             */
/*   Updated: 2024/11/02 11:10:04 by derakoto         ###   ########.fr       */
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
    while (ft_isalpha(str[i]) && str[i] != 0)
        i++;
    if (str[i] != '=')
        return (-1);
    return (0);
}
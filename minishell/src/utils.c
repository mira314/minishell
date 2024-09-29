/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:12:24 by vrandria          #+#    #+#             */
/*   Updated: 2024/09/29 16:13:37 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int print_error(char *str, char *msg, int code)
{
    ft_putstr_fd(str, STDERR_FILENO);
    if (msg)
        ft_putstr_fd(msg, STDERR_FILENO);
    ft_putchar_fd('\n', STDERR_FILENO);
    g_last_val = code;
    return (code);
}
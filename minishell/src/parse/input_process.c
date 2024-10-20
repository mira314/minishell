/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 08:24:27 by vrandria          #+#    #+#             */
/*   Updated: 2024/10/19 09:05:23 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_token *parsing_input(t_cmd *cmd, t_token *token)
{
    (void)token;
    while (cmd)
        cmd = cmd->next;
    init_input_output(cmd);
    return (0);
}
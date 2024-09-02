/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_commande_parse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 10:13:53 by vrandria          #+#    #+#             */
/*   Updated: 2024/08/31 15:46:10 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int is_built_in_cmd(char *cmd)
{
    if (ft_strncmp(cmd, "cd", 2) == 0)
        return (1);
    if (ft_strncmp(cmd, "cd..", 4) == 0)
        return (1);
    if (ft_strncmp(cmd, "pwd", 3) == 0)
        return (1);
    if (ft_strncmp(cmd, "echo", 4) == 0)
        return (1);
    return (0);
}

void exec_mini_built(char *cmd)
{
    if (ft_strncmp(cmd, "pwd",ft_strlen(cmd)) == 0)
        ft_pwd();
    if (ft_strncmp(cmd, "echo", 4) == 0)
        ft_echo(&cmd[5], 0);// a modifier apres split
}

char **splited_pipe(char  *cmd)
{
    char **splited;

    splited = ft_split(cmd, '|');
    return (splited);
}

int parse_from_prompt(t_data *data)
{
    (void)data;
    return (1);
}

int init_data(t_data *data)
{
    data->input_prompt = NULL;
    return (1);
}
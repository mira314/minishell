/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_commande_parse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 10:13:53 by vrandria          #+#    #+#             */
/*   Updated: 2024/09/18 07:48:30 by vrandria         ###   ########.fr       */
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
        ft_echo(&cmd);// a modifier apres split
    if (ft_strncmp(cmd, "cd", 2) == 0)
        mini_cd(NULL);
}

char **splited_pipe(char  *cmd)
{
    char **splited;

    splited = ft_split(cmd, '|');
    return (splited);
}

int parse_commande(t_data *data)
{

    t_cmd *cmd;

    cmd = data->cmd;
    while (cmd && cmd)
    {
        if (cmd->args)
            cmd = cmd->next;
        else
        {
            cmd->args = (char **)malloc(sizeof(char)*2);
            cmd->args[0] = ft_strdup(cmd->cmd);
            cmd->args[1] = 0;
        }
    }
    return (0);   
}


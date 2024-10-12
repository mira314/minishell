/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_commande_parse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 10:13:53 by vrandria          #+#    #+#             */
/*   Updated: 2024/10/12 10:11:09 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int handles_bultin(t_data *data)
{
    t_cmd *cmd;
    cmd = data->cmd;
    int exit;

    exit = 1;
    if (ft_strncmp(cmd->cmd, "echo", 5) == 0)
        exit = ft_echo(&(cmd->args[1]));
    else if (ft_strncmp(cmd->cmd, "pwd", 3) == 0)
        exit = ft_pwd();
    else if (ft_strncmp(cmd->cmd, "cd", 2) == 0)
        exit = mini_cd((cmd->args[1]));
    else if (is_in_path_env(cmd->cmd, data->env) != 0)
        printf("fork to do mini.cmd.c \n ");
    else
        exit = print_error(cmd->cmd, ": command not found", 127);
    data->exit_value = exit;
    return (exit);
}
int parse_commande(t_data *data)
{

    t_cmd *cmd;

    cmd = data->cmd;
    while (cmd)//a revoir
    {
        if (cmd->args)
            cmd = cmd->next;
        else
        {
            cmd->args = (char **)malloc(sizeof(char *) * 2);
            cmd->args[0] = ft_strdup(cmd->cmd);
            cmd->args[1] = 0;
        }
    }
    return (0);   
}


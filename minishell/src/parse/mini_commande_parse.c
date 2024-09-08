/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_commande_parse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 10:13:53 by vrandria          #+#    #+#             */
/*   Updated: 2024/09/03 11:14:19 by derakoto         ###   ########.fr       */
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
    if (ft_strncmp(cmd, "cd", 2) == 0)
        mini_cd(NULL);
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

void init_commad(t_data data, t_token *token)
{
    t_token *temp;
    (void)data;
    temp = token;
    (void)temp;
}

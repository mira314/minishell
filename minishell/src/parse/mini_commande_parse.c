/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_commande_parse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 10:13:53 by vrandria          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/12/07 14:08:07 by derakoto         ###   ########.fr       */
=======
/*   Updated: 2024/12/07 13:57:51 by vrandria         ###   ########.fr       */
>>>>>>> pars
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	handles_bultin(t_data *data, t_cmd *cmd)
{
	int	exit;

	exit = 1;
	if (ft_strncmp(cmd->args[cmd->offset], "echo", 5) == 0)
		exit = ft_echo(&(cmd->args[1 + cmd->offset]));
	else if (ft_strncmp(cmd->args[cmd->offset], "pwd", 4) == 0)
		exit = ft_pwd();
	else if (ft_strncmp(cmd->args[cmd->offset], "cd", 3) == 0)
		exit = mini_cd(data, cmd);
	else if (ft_strncmp(cmd->args[cmd->offset], "env", 4) == 0)
		exit = mini_env(cmd->args, data->env);
	else if (ft_strncmp(cmd->args[cmd->offset], "export", 7) == 0)
		exit = mini_export(cmd->args, &data->env);
	else if (ft_strncmp(cmd->args[cmd->offset], "unset", 6) == 0)
	{
		exit = mini_unset(data->var, cmd->args + 1);
		exit = mini_unset(data->env, cmd->args + 1);
	}
	else if (ft_strncmp(cmd->args[cmd->offset], "exit", 5) == 0)
		mini_exit(data, cmd);
	else
		return (FAIL);
	data->exit_value = exit;
	return (SUCCESS);
}

int	parse_commande(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	while (cmd)
	{
		if (cmd->args)
			cmd = cmd->next;
		else
		{
			if (cmd->cmd)
			{
				cmd->args = (char **)malloc(sizeof(char *) * 2);
				cmd->args[0] = ft_strdup(cmd->cmd);
				cmd->args[1] = 0;
			}
			cmd = cmd->next;
		}
	}
	return (0);
}

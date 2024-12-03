/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 04:42:45 by derakoto          #+#    #+#             */
/*   Updated: 2024/12/03 06:00:01 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_path(char *str)
{
	int	i;

	if (str == NULL)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (0);
		i++;
	}
	return (-1);
}

int	execute_path(t_data *data, t_cmd *cmd, char *path)
{
	int			result;
	struct stat	path_stat;

	if (stat(path, &path_stat) != -1)
	{
		if (S_ISDIR(path_stat.st_mode))
		{
			ft_putstr_fd(path, 2);
			ft_putstr_fd(": is a directory\n", 2);
			return (126);
		}
	}
	result = exec_with_fork(data, path, cmd->args + cmd->offset, data->env);
	return (result);
}

int	execute_tools(t_data *data, t_cmd *cmd, char *path)
{
	char	*total_path;
	int		exit_status;

	total_path = build_path(path, cmd->args[cmd->offset]);
	free(path);
	if (total_path == NULL)
		return (1);
	exit_status = exec_with_fork(data, total_path, cmd->args
			+ cmd->offset, data->env);
	free(total_path);
	return (exit_status);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 05:30:50 by derakoto          #+#    #+#             */
/*   Updated: 2024/12/20 07:58:06 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exec_with_fork(t_data *data, char *path, char **args, char **envs)
{
	int	pid;
	int	status;
	int	exit_status;

	pid = fork();
	if (pid == -1)
	{
		perror("Forking");
		return (1);
	}
	if (pid == 0)
	{
		errno = 0;
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (execve(path, args, envs) == -1)
			perror(path);
		free_and_exit(data, get_error_code());
	}
	else
	{
		wait(&status);
		exit_status = get_exitstatus_code(status);
	}
	return (exit_status);
}

void	exec(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	if (cmd == NULL)
		data->exit_value = 0;
	else if (cmd->next == NULL)
		data->exit_value = exec_with_redir(data, cmd);
	else
		data->exit_value = pipe_loop(data);
}

static int	did_not_find(t_data *data, t_cmd *cmd)
{
	if (is_env_unset(data->env, "PATH") == 0)
		return (execute_path(data, cmd, cmd->args[cmd->offset]));
	else
		return (print_error(cmd->args[cmd->offset],
				": command not found", 127));
}

int	exec_one_cmd(t_data	*data, t_cmd *cmd)
{
	char	*path;
	int		exit_status;

	if (cmd->cmd == NULL)
		return (0);
	if (handle_var(cmd->args, &data->var, &cmd->offset) == SUCCESS)
		return (0);
	if (ft_strncmp("..", cmd->args[cmd->offset], 3) == 0
		|| ft_strncmp(".", cmd->args[cmd->offset], 2) == 0)
		return (print_error(cmd->args[cmd->offset],
				": command not found", 127));
	if (handles_bultin(data, cmd, &exit_status) == SUCCESS)
		return (exit_status);
	path = is_in_path_env(cmd->args[cmd->offset], data->var);
	if (path == NULL)
		path = is_in_path_env(cmd->args[cmd->offset], data->env);
	if (path != NULL)
		exit_status = execute_tools(data, cmd, path);
	else if (is_path(cmd->args[cmd->offset]) == 0)
		exit_status = execute_path(data, cmd, cmd->args[cmd->offset]);
	else
		exit_status = did_not_find(data, cmd);
	return (exit_status);
}

int	exec_with_redir(t_data *data, t_cmd *cmd)
{
	int		fd_in_backup;
	int		fd_out_backup;
	int		exit_status;

	exit_status = 0;
	fd_out_backup = dup(1);
	fd_in_backup = dup(0);
	if (handle_redir(cmd->io) == -1)
	{
		dup2(fd_out_backup, 1);
		dup2(fd_in_backup, 0);
		clear_doc(cmd->io->outputs);
		return (1);
	}
	exit_status = exec_one_cmd(data, cmd);
	clear_doc(cmd->io->outputs);
	dup2(fd_out_backup, 1);
	dup2(fd_in_backup, 0);
	return (exit_status);
}

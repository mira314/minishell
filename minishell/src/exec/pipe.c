/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 06:06:40 by derakoto          #+#    #+#             */
/*   Updated: 2024/11/25 18:15:10 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	pipe_loop(t_data *data)
{
	int		cmd_count;
	int		**pipe_fds;
	int		i;
	int		status;
	t_cmd	*current_cmd;

	current_cmd = data->cmd;
	cmd_count = count_cmd(current_cmd);
	pipe_fds = create_pipes(cmd_count - 1);
	if (init_pipes(pipe_fds, cmd_count - 1) == -1)
		return (1);
	fork_and_execute(data, pipe_fds, current_cmd, cmd_count);
	close_all_pipes(pipe_fds, cmd_count - 1);
	i = -1;
	while (++i < cmd_count)
		wait (&status);
	clean_pipes(pipe_fds, cmd_count - 1);
	return (WEXITSTATUS(status));
}

void	fork_and_execute(t_data *data, int **pipes, t_cmd *cmd, int cmd_count)
{
	int	pid;
	int	exit_code;
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
		{
			close_unused_pipe(pipes, cmd_count - 1, i);
			if (i == 0)
				exit_code = (fork_fun(NULL, pipes[i], data, cmd));
			else if (i == cmd_count -1)
				exit_code = (fork_fun(pipes[i - 1], NULL, data, cmd));
			else
				exit_code = fork_fun(pipes[i - 1], pipes[i], data, cmd);
			clean_pipes(pipes, cmd_count - 1);
			free_and_exit(data, exit_code);
		}
		cmd = cmd->next;
		i++;
	}
}

int	fork_fun(int *input, int *output, t_data *data, t_cmd *cmd)
{
	int	result;

	if (input != NULL)
	{
		close(input[1]);
		dup2(input[0], 0);
		close(input[0]);
	}
	if (output != NULL)
	{
		close(output[0]);
		dup2(output[1], 1);
		close(output[1]);
	}
	result = exec_with_redir(data, cmd);
	return (result);
}
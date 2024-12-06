/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 06:06:40 by derakoto          #+#    #+#             */
/*   Updated: 2024/12/06 06:53:17 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	pipe_loop(t_data *data)
{
	int		cmd_count;
	int		**pipe_fds;
	int		status;
	t_cmd	*current_cmd;

	current_cmd = data->cmd;
	cmd_count = count_cmd(current_cmd);
	pipe_fds = create_pipes(cmd_count - 1);
	if (init_pipes(pipe_fds, cmd_count - 1) == -1)
		return (1);
	status = fork_and_execute(data, pipe_fds, current_cmd, cmd_count);
	clean_pipes(pipe_fds, cmd_count - 1);
	return (status);
}

int	wait_and_return_exit_status(int *pids, int cmd_count)
{
	int	status;
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		if (i != cmd_count - 1)
			waitpid (pids[i], NULL, 0);
		else
			waitpid (pids[i], &status, 0);
		i++;
	}
	free(pids);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (WTERMSIG(status));
}

int	fork_and_execute(t_data *data, int **pipes, t_cmd *cmd, int cmd_count)
{
	int	*pids;
	int	exit_code;
	int	i;

	pids = (int *)malloc(sizeof(int) * cmd_count);
	i = 0;
	while (i < cmd_count)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			return (1);
		if (pids[i] == 0)
		{
			free(pids);
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
	close_all_pipes(pipes, cmd_count - 1);
	return (wait_and_return_exit_status(pids, cmd_count));
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

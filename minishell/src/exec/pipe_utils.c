/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 04:38:51 by derakoto          #+#    #+#             */
/*   Updated: 2024/12/06 08:42:31 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	count_cmd(t_cmd *cmd)
{
	int	result;

	result = 0;
	while (cmd)
	{
		result++;
		cmd = cmd->next;
	}
	return (result);
}

int	**create_pipes(int pipe_count)
{
	int	**result;
	int	i;

	result = (int **)malloc(sizeof(int *) * pipe_count);
	if (result == NULL)
		return (NULL);
	result[0] = NULL;
	i = 1;
	while (i < pipe_count - 1)
	{
		result[i] = (int *)malloc(sizeof(int) * 2);
		if (result[i] == NULL)
		{
			clean_pipes(result, i);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}

int	init_pipes(int **pipe_fds, int size)
{
	int	i;

	if (pipe_fds == NULL)
		return (-1);
	i = 1;
	while (i < size - 1)
	{
		if (pipe(pipe_fds[i]) == -1)
		{
			close_all_pipes(pipe_fds, i + 1);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	on_forking_error_pipe(int *fds)
{
	perror("Forking");
	close_one_pipe_fd(fds);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_finish.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 06:09:38 by derakoto          #+#    #+#             */
/*   Updated: 2024/12/06 06:52:46 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	close_unused_pipe(int **pipe_fds, int size, int current_index)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (i != current_index && i != current_index - 1)
			close_one_pipe_fd(pipe_fds[i]);
		i++;
	}
}

void	close_one_pipe_fd(int *fds)
{
	if (fds == NULL)
		return ;
	close(fds[0]);
	close(fds[1]);
}

void	close_all_pipes(int **pipe_fds, int size)
{
	int	i;

	if (pipe_fds == NULL)
		return ;
	i = 0;
	while (i < size)
	{
		close_one_pipe_fd(pipe_fds[i]);
		i++;
	}
}

void	clean_pipes(int **pipes, int size)
{
	int	i;

	if (pipes == NULL)
		return ;
	i = 0;
	while (i < size)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

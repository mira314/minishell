/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 04:32:27 by derakoto          #+#    #+#             */
/*   Updated: 2024/12/07 20:54:23 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	on_redir_error(char *filename)
{
	perror(filename);
	return (-1);
}

int	redir_input(t_input *file)
{
	int		input;
	int		i;

	i = 0;
	while (file[i].filename != 0)
	{
		input = open(file[i].filename, O_RDONLY);
		if (input == -1)
			return (on_redir_error(file[i].filename));
		if (file[i + 1].filename == NULL)
			dup2(input, 0);
		close(input);
		i++;
	}
	return (0);
}

int	is_still_another(t_output *file, int mode1, int mode2)
{
	int	i;

	if (file == NULL)
		return (1);
	i = 0;
	while (file[i].filename != 0)
	{
		if (file[i].mode == mode1 || file[i].mode == mode2)
			return (0);
		i++;
	}
	return (1);
}

int	redir_output(t_output *file)
{
	int	open_mode;
	int	fd;
	int	i;

	i = 0;
	while (file[i].filename != 0)
	{
		if (file[i].mode == APPEND || file[i].mode == TRUNC)
		{
			open_mode = O_WRONLY | O_CREAT | O_TRUNC;
			if (file[i].mode == APPEND)
				open_mode = O_WRONLY | O_CREAT | O_APPEND;
			fd = open(file[i].filename, open_mode, 0644);
			if (fd == -1)
				return (on_redir_error(file[i].filename));
			if (is_still_another(file + i + 1, APPEND, TRUNC) == 0)
				close(fd);
			else
			{
				if (dup2(fd, 1) == -1)
					return (on_redir_error(file[i].filename));
				close (fd);
			}
			i++;
		}
		else if (file[i].mode == INPUT || file[i].mode == HEREDOC)
		{
			fd = open(file[i].filename, O_RDONLY);
			if (fd == -1)
				return (on_redir_error(file[i].filename));
			if (is_still_another(file + i + 1, INPUT, HEREDOC))
				dup2(fd, 0);
			close(fd);
			i++;
		}
		
	}
	return (0);
}

int	handle_redir(t_io_fd *io)
{
	if (redir_input(io->inputs) == -1)
		return (-1);
	if (redir_output(io->outputs) == -1)
		return (-1);
	return (0);
}

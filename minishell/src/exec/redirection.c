/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 04:32:27 by derakoto          #+#    #+#             */
/*   Updated: 2024/12/11 10:46:42 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	on_redir_error(char *filename)
{
	perror(filename);
	return (-1);
}

static int	is_still_another(t_io_file *file, int mode1, int mode2)
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

int	redir_input(t_io_file *file, int i)
{
	int		fd;

	fd = open(file[i].filename, O_RDONLY);
	if (fd == -1)
		return (on_redir_error(file[i].filename));
	if (is_still_another(file + i + 1, INPUT, HEREDOC))
		dup2(fd, 0);
	close(fd);
	return (0);
}

int	redir_output(t_io_file *file, int i)
{
	int	open_mode;
	int	fd;

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
	return (0);
}

int	handle_redir(t_io_fd *io)
{
	int			i;
	t_io_file	*file;

	file = io->outputs;
	if (file == NULL)
		return (-1);
	i = 0;
	while (file[i].filename != 0)
	{
		if (file[i].mode == APPEND || file[i].mode == TRUNC)
		{
			if (redir_output(file, i) == -1)
				return (-1);
		}
		else if (file[i].mode == INPUT || file[i].mode == HEREDOC)
		{
			if (redir_input(file, i) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_int_and_out.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 08:27:39 by vrandria          #+#    #+#             */
/*   Updated: 2024/12/08 06:58:36 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_output	*init_output(t_output **output)
{
	*output = (t_output *)malloc(sizeof(t_output));
	if (*output == NULL)
		return (NULL);
	(*output)->filename = NULL;
	(*output)->mode = TRUNC;
	return (*output);
}

void	init_input_output(t_cmd *cmd)
{
	t_io_fd	*io;

	if (cmd->io == 0)
	{
		cmd->io = (t_io_fd *)malloc(sizeof(t_io_fd));
		if (!cmd->io)
			return ;
		io = cmd->io;
		init_output(&io->outputs);
		io->input_fd = -1;
		io->output_fd = -1;
		io->stdin = -1;
		io->stdout = -1;
		io->quote_status = 0;
	}
}

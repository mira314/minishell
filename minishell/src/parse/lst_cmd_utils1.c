/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:03:07 by vrandria          #+#    #+#             */
/*   Updated: 2024/11/26 10:11:47 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static t_cmd	*lst_del_cmd(t_cmd *cmd)
{
	t_cmd	*current;
	t_cmd	*next_cmd;

	current = cmd;
	while (current)
	{
		next_cmd = current->next;
		mini_tbl_free(current->args);
		free(current->cmd);
		clear_io(current->io);
		free(current->io);
		free(current);
		current = next_cmd;
	}
	return (NULL);
}

void	clear_outputs(t_output *output)
{
	int	i;

	if (output == NULL)
		return ;
	i = 0;
	while (output[i].filename != NULL)
	{
		free(output[i].filename);
		i++;
	}
}

void	clear_inputs(t_input *input)
{
	int	i;

	if (input == 0)
		return ;
	i = 0;
	while (input[i].filename != NULL)
	{
		free(input[i].filename);
		i++;
	}
}

void	clear_io(t_io_fd *io)
{
	if (io == NULL)
		return ;
	clear_inputs(io->inputs);
	free(io->inputs);
	clear_outputs(io->outputs);
	free(io->outputs);
}

void	clear_lst_cmd(t_data *data)
{
	if (data->cmd != 0)
	{
		lst_del_cmd(data->cmd);
		data->cmd = NULL;
	}
}

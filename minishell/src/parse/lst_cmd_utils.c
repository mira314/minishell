/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 07:51:18 by vrandria          #+#    #+#             */
/*   Updated: 2024/11/24 11:09:56 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*new;
	t_cmd	*tmp;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (0);
	tmp = init_cmd(new);
	if (!tmp)
	{
		free(new);
		return (0);
	}
	return (tmp);
}

t_cmd	*lst_add_back_cmd(t_cmd *cmd, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	if (tmp == 0)
	{
		cmd = new_cmd;
		return (cmd);
	}
	if (tmp && new_cmd)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cmd;
		new_cmd->prev = tmp;
	}
	return (cmd);
}



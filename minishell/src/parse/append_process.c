/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:41:59 by vrandria          #+#    #+#             */
/*   Updated: 2024/12/08 07:07:14 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_io_file	*add_output(t_cmd *cmd, char *filename, int mode)
{
	int			i;
	int			count;
	t_io_file	*tmp;
	t_io_file	*new;

	i = 0;
	count = 0;
	tmp = cmd->io->outputs;
	while (tmp[i].filename)
		i++;
	new = malloc((sizeof(t_io_file) * (i + 2)));
	if (!new)
		return (NULL);
	while (count < i)
	{
		new[count].filename = tmp[count].filename;
		new[count].mode = tmp[count].mode;
		count++;
	}
	new[count].filename = ft_strdup(filename);
	new[count].mode = mode;
	new[count + 1].filename = NULL;
	free(tmp);
	return (new);
}

t_token	*parsing_append(t_cmd *cmd, t_token *token)
{
	if (cmd == NULL || token == NULL)
		return (NULL);
	while (cmd->next)
		cmd = cmd->next;
	cmd->io->outputs = add_output(cmd, token->next->str, APPEND);
	if (token->next->next)
	{
		token = token->next->next;
	}
	else
		token = token->next;
	return (token);
}

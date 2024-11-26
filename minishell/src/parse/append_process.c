/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:41:59 by vrandria          #+#    #+#             */
/*   Updated: 2024/11/26 07:26:27 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_output	*add_output(t_cmd *cmd, t_token *token, int mode)
{
	int			i;
	int			count;
	t_output	*tmp;
	t_output	*new;

	i = 0;
	count = 0;
	tmp = cmd->io->outputs;
	while (tmp[i].filename)
		i++;
	new = malloc((sizeof(t_output) * (i + 2)));
	if (!new)
		return (NULL);
	while (count < i)
	{
		new[count].filename = tmp[count].filename;
		new[count].mode = tmp[count].mode;
		count++;
	}
	new[count].filename = ft_strdup(token->str);
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
	cmd->io->outputs = add_output(cmd, token->next, APPEND);
	if (token->next->next)
	{
		token = token->next->next;
	}
	else
		token = token->next;
	return (token);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trunc_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:44:56 by vrandria          #+#    #+#             */
/*   Updated: 2024/12/07 20:28:27 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_token	*parsing_trunc(t_cmd *cmd, t_token *token)
{
	if (cmd == NULL || token == NULL)
		return (NULL);
	while (cmd->next)
		cmd = cmd->next;
	cmd->io->outputs = add_output(cmd, token->next->str, TRUNC);
	if (token->next->next)
	{
		token = token->next->next;
	}
	else
		token = token->next;
	return (token);
}

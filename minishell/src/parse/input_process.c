/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 08:24:27 by vrandria          #+#    #+#             */
/*   Updated: 2024/12/07 21:29:07 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_token	*parsing_input(t_cmd *cmd, t_token *token)
{
	char	*filename;

	if (cmd == NULL)
		return (NULL);
	while (cmd->next)
		cmd = cmd->next;
	filename = token->next->str;
	cmd->io->outputs = add_output(cmd, filename, INPUT);
	if (token->next->next)
		token = token->next->next;
	else
		token = token->next;
	return (token);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:00:24 by vrandria          #+#    #+#             */
/*   Updated: 2024/10/12 10:41:17 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_token *echo_parsing_arg(t_token *token, t_cmd *cmd)
{
	int argc;
	int i;

	i = 0;
	argc = arg_count(token);
	cmd->args = (char **)malloc(sizeof(char) * (argc + 1));
	if (!cmd->args)
		return (0);
	cmd->args[i] = ft_strdup(cmd->cmd);
	i++;
	while (token->type_token == VAR || token->type_token == WORD)
	{
		if (token->inner_join == 1)
			printf("il echo parsing dans var non gere \n");// to do
		else
			cmd->args[i] = ft_strdup(token->str);
		i++;
		token = token->next;
	}
	cmd->args[i] = 0;
	return (token);
}

t_token *parsins_word(t_cmd *cmd, t_token *token)
{
	while (token->type_token == WORD || token->type_token == VAR)
	{
		while(cmd->next)
			cmd = cmd->next;
		if (token->prev == 0 || (token->prev && token->prev->type_token == PIPE) || cmd->cmd == 0)
		{
			if (token->type_token == VAR && (ft_strchr(token->str, 32)))
				printf("il faut spliter car espace trouve");
			else
				cmd->cmd =ft_strdup(token->str);// a freee e
			token = token->next;
		}
		else
		{
			token = split_args(token, cmd);
		}
		
	}
	return (token);
}


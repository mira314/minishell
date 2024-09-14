/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:00:24 by vrandria          #+#    #+#             */
/*   Updated: 2024/09/14 10:03:27 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_token *parsins_word(t_cmd *cmd, t_token *token)
{
	while (token->type_token == WORD || token->type_token == VAR)
	{
		while(cmd->next)
			cmd = cmd->next;
		if (token->prev == 0 || (token->prev && token->prev->type_token == PIPE) || cmd->cmd == 0)
		{
			if (token->type_token == VAR && (ft_strchr(token->str, ' ')) != 0)
				printf("il faut spliter");
			else
			{
				cmd->cmd =ft_strdup(token->str);// a freee e
				printf("else dans parsing");
			}
			token = token->next;
		}
		else
			printf("%s\n",token->str);
		printf("la commade est %s\n", cmd->cmd);
	}
	return (token);
}


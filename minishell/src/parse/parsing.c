/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:00:24 by vrandria          #+#    #+#             */
/*   Updated: 2024/09/18 08:18:25 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int arg_count(t_token *token)
{
	int count;

	count = 0;
	while (token && (token->type_token == WORD || token->type_token == VAR))
	{
		count++;
		token = token->next;
	}
	return (count);
}

t_token *split_args(t_token *token, t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd, "echo", 4) == 0)
	{
		printf("(parsing)parsing des argument echo car la commande est %s\n", cmd->cmd);
		return(token->next);
	}
	else
	{
		if (!cmd->args)
		{
			printf("la commande n est pas echo sans argument mais %s (parsing.c)\n", cmd->cmd);
			return(token->next);
		}
		else
		{
			printf("la commande n est pas echo avec argument mais %s (parsing.c)\n", cmd->cmd);
			return(token->next);
		}
	}
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
			{
				cmd->cmd =ft_strdup(token->str);// a freee e
				printf("else dans parsing \n");
			}
			token = token->next;
		}
		else
		{
			printf("gestion des argume de la commade dams parsing\n");
			token = split_args(token, cmd);
		}
		
	}
	printf("la commade est %s\n", cmd->cmd);
	return (token);
}


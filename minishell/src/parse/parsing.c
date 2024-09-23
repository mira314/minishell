/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:00:24 by vrandria          #+#    #+#             */
/*   Updated: 2024/09/23 08:44:14 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int arg_count(t_token *token)
{
	int count;

	count = 0;
	while (token && (token->type_token == WORD || token->type_token == VAR))
	{
		//les cquote est le variable ne sont pas prise en cmpte pour le moment
		count++;
		token = token->next;
	}
	return (count);
}


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
		{
			printf("il echo parsing dans var non gere \n");
		}
		else
			cmd->args[i] = ft_strdup(token->temp);
		i++;
		token = token->next;
	}
	cmd->args[i] = 0;
	return (token);

}
char **ft_split_expansion(int len, t_token *token, t_cmd *cmd, char **tab)
{
	int i;

	i = 0;
	while (len > i)
	{
		tab[i] = cmd->args[i];
		i++;
	}
	while (token->type_token == VAR || token->type_token == WORD)
	{
		if (token->inner_join == 1)
		{	
			printf("%s\n", "var non gere sur ft_split_expansion");//////////////////
		}
		else
			tab[i] = ft_strdup(token->str);
		i++;
		token = token->next;
	}
	tab[i] = 0;
	return (tab);
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
			printf("gestion des argume de la commade dams parsing\n");
			token = split_args(token, cmd);
		}
		
	}
	printf("la commade est [%s]\n", cmd->cmd);
	return (token);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 10:00:24 by vrandria          #+#    #+#             */
/*   Updated: 2024/10/19 15:08:49 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void split_token(t_cmd *cmd, t_token *token)
{
	t_token *new;
	t_token *tmp;
	t_token *alloc;
	char **tab;
	int i;

	new = 0;
	tab = ft_split(token->str, 32);
	if (!tab)
		return ;
	cmd->cmd = ft_strdup(tab[0]);
	if (tab[1])
		new = new_token(ft_strdup(tab[1]),0 , WORD);
	tmp = new;
	i = 2;
	while (tab[i])
	{
		alloc = new_token(ft_strdup(tab[i]),0 , WORD);
		new = lst_add_back_token(new, alloc);
	}
	new = split_args(new, cmd);
	lst_clear_all_token(tmp);
	clear_tab(tab);
}

t_token *echo_parsing_arg(t_token *token, t_cmd *cmd)
{
	int argc;
	int i;

	i = 0;
	argc = 0;
	argc = arg_count(token);
	cmd->args = (char **)malloc(sizeof(char *) * (argc + 2));
	if (!cmd->args)
		return (0);
	cmd->args[i++] = ft_strdup(cmd->cmd);
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
				split_token(cmd, token);
			else
				cmd->cmd = ft_strdup(token->str);
			token = token->next;
		}
		else
		{
			token = split_args(token, cmd);
		}
		
	}
	return (token);
}


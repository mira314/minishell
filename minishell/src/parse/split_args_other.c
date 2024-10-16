/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_other.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 07:28:22 by vrandria          #+#    #+#             */
/*   Updated: 2024/10/16 08:15:09 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int count_word(t_token *token)
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

t_token *new_args_for_other_cmd(t_token *token , t_cmd *cmd)
{
	int i;
	t_token *tmp;

	i = 0;

	tmp = token;
	cmd->args = malloc(sizeof(char) * (count_word(tmp) + 2));
	if (!cmd->args)
		return (0);
	cmd->args[i] = ft_strdup(cmd->cmd);
	i++;
	while (tmp->type_token == WORD || tmp->type_token == VAR)
	{
		cmd->args[i] = ft_strdup(tmp->str);
		i++;
		tmp = tmp->next;
	}
	cmd->args[i] = 0;
	return (tmp);
}

t_token *add_args_for_other_cmd(t_token *token, t_cmd *cmd)
{
	int i;
	int len;
	char **new_chain;
	t_token *old;

	i = 0;
	len = 0;
	old = token;
	while (token->type_token == WORD || token->type_token == VAR)
	{
		i++;
		token = token->next;
	}
	while (cmd->args[len])
		len++;
	new_chain = malloc(sizeof(char) * (i + len + 1));
	if (!new_chain)
		return (0);
	new_chain = copy_new_tab(len, new_chain, old, cmd);
	free(cmd->args);
	cmd->args = new_chain;
	return (token);
}
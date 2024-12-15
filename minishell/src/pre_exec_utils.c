/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 20:55:32 by derakoto          #+#    #+#             */
/*   Updated: 2024/12/15 21:30:38 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_tokentype_to_word(t_token *token)
{
	if (token == NULL)
		return ;
	while (token)
	{
		token->type_token = WORD;
		token = token->next;
	}
}

t_token	*replace_token(t_data *data, t_token *var_token, t_token *token)
{
	t_token	*result;

	if (data == NULL)
		return (NULL);
	result = data->token;
	if (var_token == NULL || token == NULL)
		return (result);
	lst_add_back_token(var_token, token->next);
	var_token->prev = token->prev;
	if (token->prev == NULL)
		result = var_token;
	else
		token->prev->next = var_token;
	return (result);
}

void	expand_token_str(t_data *data, t_token *token)
{
	if (data == NULL || token == NULL)
		return ;
	if (token->prev && token->prev->type_token == HEREDOC)
		token->str = var_expand(data, token->str, 1);
	else
		token->str = var_expand(data, token->str, 0);
}
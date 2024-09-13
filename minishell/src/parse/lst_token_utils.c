/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_token_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 08:46:57 by vrandria          #+#    #+#             */
/*   Updated: 2024/09/13 13:29:20 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_token	*new_token(char *str, int flag, int type_token)
{
	t_token *token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (0);
	token->str = str;
	token->temp = ft_strdup(str);
	if (type_token != WORD)
		token->temp = 0;
	token->check_var = 0;
	token->inner_join = 0;
	token->type_token = type_token;
	token->flag = flag;
	token->prev = 0;
	token->next = 0;
	return (token);
}

t_token	*lst_add_back_token(t_token *token, t_token *new_token)
{
	t_token *tmp;

	tmp = token;
	if (!tmp)
		return (new_token);
	if(tmp && new_token)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token;
		new_token->prev = tmp;
	}
	return (token);
}

//it's possible to free all value token here, to check if it's necessary
t_token	*lst_del_token(t_token *token)
{
	t_token *tmp;

	tmp = token->next;
	free(token->temp);
	free(token);
	return (tmp);
}

void lst_clear_all_token(t_token *token)
{
	while (token)
		token = lst_del_token(token);
}
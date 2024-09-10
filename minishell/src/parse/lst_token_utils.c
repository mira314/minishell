/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_token_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 08:46:57 by vrandria          #+#    #+#             */
/*   Updated: 2024/09/10 09:11:04 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_token	*new_token(char *str, char *lastadd, int flag, int type_token)
{
	t_token *token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (0);
	token->str = str;
	token->temp = lastadd;
	token->check_var = 0;
	token->inner_join = 0;
	token->type_token = type_token;
	token->flag = flag;
	token->prev = 0;
	token->next = 0;
	return (token);
}
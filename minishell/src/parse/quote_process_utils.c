/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_process_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 12:43:51 by vrandria          #+#    #+#             */
/*   Updated: 2024/12/18 07:44:02 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	is_protected_quote(char *str, int i)
{
	int	quote;

	quote = is_quote(str[i]);
	if (i != 0 && str[i - 1] == 14)
		quote = EMPTY;
	return (quote);
}

int	check_quote_flag(t_token *token, int i)
{
	if (token->str[i] == 39 && token->flag == EMPTY)
		return (1);
	if (token->str[i] == 34 && token->flag == EMPTY)
		return (1);
	return (0);
}

int	switch_flag_token(int i, t_token *token)
{
	if (token->str[i] == 34)
		token->flag = DOUBLE_QUOTE;
	if (token->str[i] == 39)
		token->flag = ONE_QUOTE;
	i++;
	return (i);
}

int	is_char_protection(char c, int *count)
{
	if (c == 14)
	{
		*count = *count + 2;
		return (1);
	}
	return (0);
}

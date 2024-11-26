/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_process_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 12:43:51 by vrandria          #+#    #+#             */
/*   Updated: 2024/11/26 10:25:49 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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

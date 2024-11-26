/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 07:35:00 by vrandria          #+#    #+#             */
/*   Updated: 2024/11/26 07:57:23 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	check_quote(int flag, int input)
{
	if (input == 39 && flag == EMPTY)
		flag = ONE_QUOTE;
	else if (input == 34 && flag == EMPTY)
		flag = DOUBLE_QUOTE;
	else if (input == 39 && flag == ONE_QUOTE)
		flag = EMPTY;
	else if (input == 34 && flag == DOUBLE_QUOTE)
		flag = EMPTY;
	return (flag);
}

int	what_is_sep(char *str, int i)
{
	if (str[i] >= 9 && str[i] <= 13)
		return (SPACES);
	if (str[i] == 32)
		return (SPACES);
	if (str[i] == '<' && str[i + 1] != '<')
		return (INPUT);
	if (str[i] == '>' && str[i + 1] != '>')
		return (TRUNC);
	if (str[i] == '<' && str[i + 1] == '<')
		return (HEREDOC);
	if (str[i] == '>' && str[i + 1] == '>')
		return (APPEND);
	if (str[i] == '\0')
		return (END);
	if (str[i] == '|')
		return (PIPE);
	return (0);
}

int	token_split_word_and_sep(char *str, int start, t_data *data, int *i)
{
	int	type_token;

	type_token = what_is_sep(str, (*i));
	if (type_token)
	{
		if ((*i) != 0 && (what_is_sep(str, (*i) - 1)) == 0)
			token_word(&data->token, str, (*i), start);
		if (type_token == HEREDOC || type_token == PIPE
			||type_token == APPEND || type_token == END
			||type_token == TRUNC || type_token == INPUT)
		{
			token_other(&data->token, str, (*i), type_token);
			if (type_token == HEREDOC || type_token == APPEND)
				(*i)++;
		}
		start = (*i) + 1;
	}
	return (start);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 07:27:36 by vrandria          #+#    #+#             */
/*   Updated: 2024/10/26 07:28:09 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int count_str_betweenquote(char *str, int count, int flag)
{
	int i;

	i = count;
	while (str[i])
	{
		if ((flag == EMPTY) && (str[i] == 39 || str[i] == 34))
		{
			if (str[i] == 34)
				flag = DOUBLE_QUOTE;
			if (str[i] == 39)
				flag = ONE_QUOTE;
			i++;
		}
		else if ((str[i] == 39 && flag == ONE_QUOTE) || (str[i] == 34 && DOUBLE_QUOTE))
		{
			flag = EMPTY;
			i++;
		}
		else
		{
			i++;
			count++;
		}
		return (count);
	}
	
}

static int quote_between_str(t_token *token)
{
	char *str;
	int i;

	i = 0;
	str = token->str;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
			return (1);
		i++;
	}
	return (0);
}

t_token *trim_quote(t_token *token, int j)
{
	char *new;
	int i;
	int len;


	i = 0;
	len = count_str_betweenquote(token->str, i, 0);
	new = malloc(sizeof(char) * len + 1);
	if (!new)
		return (0);
	
}

void quote_process(t_data *data)
{
	t_token *current;

	current = data->token;
	while (current)
	{
		if (quote_between_str(current) == 1)
		{
			if (!current->prev)
				current = trim_quote(current, 0);
			else if (current->prev->type_token != HEREDOC)
				current = trim_quote(current, 0);
		}
		current = current->next;
	}
}
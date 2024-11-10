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

int check_quote_flag(t_token *token, int i)
{
	if (token->str[i] == 39 && token->flag == EMPTY)
		return (1);
	if (token->str[i] == 34 && token->flag == EMPTY)
		return (1);
	return (0);
}

int switch_flag_token(int i, t_token *token)
{
	if (token->str[i] == 34)
		token->flag = DOUBLE_QUOTE;
	if (token->str[i] == 39)
		token->flag = ONE_QUOTE;
	i++;
	return (i);
}

int switch_flag_token_empty(int i, t_token *token)
{
	if (token->str[i] == 39 && token->flag == ONE_QUOTE)
	{
		token->flag = EMPTY;
		i++;
		return (i);
	}
	else if (token->str[i] == 34 && token->flag == DOUBLE_QUOTE)
	{
		token->flag = EMPTY;
		i++;
		return (i);
	}
	return (i);
}

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
	}
	return (count);
	
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
	while (token->str[i])
	{
		if (check_quote_flag(token, i) == 1)
		{
			i = switch_flag_token(i ,token);
			continue ;
		}
		else if (switch_flag_token_empty(i, token) != i)
			continue ;
		new[j++] = token->str[i++];
	}
	new[j] = 0;
	free(token->str);
	token->str = new;
	token->inner_join = 1;
	return (token);
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
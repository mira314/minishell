/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 07:27:36 by vrandria          #+#    #+#             */
/*   Updated: 2024/12/16 21:40:20 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	count_str_betweenquote(char *str, int count, int flag)
{
	int	i;

	i = count;
	while (str[i])
	{
		if ((flag == EMPTY) && (str[i] == 39 || str[i] == 34))
		{
			if (str[i] == 34)
				flag = DOUBLE_QUOTE;
			if (str[i] == 39)
				flag = ONE_QUOTE;
		}
		else if ((str[i] == 39 && flag == ONE_QUOTE)
			|| (str[i] == 34 && DOUBLE_QUOTE))
		{
			flag = EMPTY;
		}
		else
			count++;
		i++;
	}
	return (count);
}

static int	quote_between_str(t_token *token)
{
	char	*str;
	int		i;

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

int	is_quote(char c)
{
	if (c == '"')
		return (DOUBLE_QUOTE);
	else if (c == '\'')
		return (ONE_QUOTE);
	return (EMPTY);
}

t_token	*trim_quote(t_token *token, int j)
{
	char	*new;
	int		i;
	int		len;
	int		quote;

	len = count_str_betweenquote(token->str, 0, 0);
	new = malloc(sizeof(char) * len + 2);
	if (!new)
		return (0);
	i = -1;
	while (token->str[++i])
	{
		quote = is_quote(token->str[i]);
		if (quote != EMPTY && token->flag == quote)
			token->flag = EMPTY;
		else if (quote != EMPTY && token->flag == EMPTY)
			token->flag = quote;
		else
			new[j++] = token->str[i];
	}
	new[j] = 0;
	free(token->str);
	token->str = new;
	token->inner_join = 1;
	return (token);
}

void	quote_process(t_data *data)
{
	t_token	*current;

	current = data->token;
	while (current)
	{
		if (quote_between_str(current) == 1)
		{
			/*if (!current->prev)
				current = trim_quote(current, 0);
			else if (current->prev->type_token != HEREDOC)
				current = trim_quote(current, 0);*/
			current = trim_quote(current, 0);
		}
		current = current->next;
	}
}

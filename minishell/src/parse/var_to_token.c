/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_to_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 09:21:23 by derakoto          #+#    #+#             */
/*   Updated: 2024/12/16 08:44:23 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	what_is_sep1(char *str, int i)
{
	if (str[i] >= 9 && str[i] <= 13)
		return (SPACES);
	if (str[i] == 32)
		return (SPACES);
	/*if (str[i] == '<' && str[i + 1] != '<')
		return (INPUT);
	if (str[i] == '>' && str[i + 1] != '>')
		return (TRUNC);
	if (str[i] == '<' && str[i + 1] == '<')
		return (HEREDOC);
	if (str[i] == '>' && str[i + 1] == '>')
		return (APPEND);*/
	if (str[i] == '\0')
		return (END);
	//if (str[i] == '|')
	//	return (PIPE);
	return (0);
}

void	split_var_to_token(t_token **token, char *input, int flag)
{
	int	i;
	int	start;
	int	limit;

	i = 0;
	start = 0;
	limit = ft_strlen(input);
	while (limit >= i)
	{
		flag = check_quote(flag, (int)input[i]);
		if (flag == EMPTY)
			start = split_var_helper(input, start, token, &i);
		i++;
	}
}

int	split_var_helper(char *str, int start, t_token **token, int *i)
{
	int	type_token;

	type_token = what_is_sep1(str, (*i));
	if (type_token)
	{
		if ((*i) != 0 && (what_is_sep1(str, (*i) - 1)) == 0)
			token_word(token, str, (*i), start);
		if (type_token == HEREDOC || type_token == PIPE
			||type_token == APPEND || type_token == TRUNC
			|| type_token == INPUT)
		{
			token_other(token, str, (*i), type_token);
			if (type_token == HEREDOC || type_token == APPEND)
				(*i)++;
		}
		start = (*i) + 1;
	}
	return (start);
}

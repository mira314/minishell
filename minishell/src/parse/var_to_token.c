/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_to_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 09:21:23 by derakoto          #+#    #+#             */
/*   Updated: 2024/12/18 09:15:13 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	what_is_sep_var(char *str, int i)
{
	if (str[i] >= 9 && str[i] <= 13)
		return (SPACES);
	if (str[i] == 32)
		return (SPACES);
	if (str[i] == '\0')
		return (END);
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
		if (i == 0 && (input[i] == '"' || input[i] == '\''))
			flag = check_quote(flag, (int)input[i]);
		else if (i != 0 && input[i - 1] != 14 && is_quote(input[i]))
			flag = check_quote(flag, (int)input[i]);
		if (flag == EMPTY)
			start = split_var_helper(input, start, token, &i);
		i++;
	}
}

int	split_var_helper(char *str, int start, t_token **token, int *i)
{
	int	type_token;

	type_token = what_is_sep_var(str, (*i));
	if (type_token)
	{
		if ((*i) != 0 && (what_is_sep_var(str, (*i) - 1)) == 0)
			token_word(token, str, (*i), start);
		start = (*i) + 1;
	}
	return (start);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:13:20 by vrandria          #+#    #+#             */
/*   Updated: 2024/10/19 13:29:44 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	token_word(t_token **token, char *str, int i, int start)
{
	int		j;
	char	*arg;
	t_token	*new;

	j = 0;
	arg = (char *)malloc(sizeof(char) * (i - start) + 1);
	if (!arg)
		return (1);
	while (i > start)
	{
		arg[j] = str[start];
		j++;
		start++;
	}
	arg[j] = 0;
	new = new_token(arg, 0, WORD);
	if (!new)
	{
		free(arg);
		return (1);
	}
	
	(*token) = lst_add_back_token((*token), new);
	return (0);
}

int	token_other(t_token **token, char *str, int i, int type_token)
{
	char	*arg;
	t_token	*new;

	if (type_token == APPEND || type_token == HEREDOC)
	{
		arg = (char *)malloc(3);
		if (!arg)
			return (1);
		arg[0] = str[i];
		arg[1] = str[i + 1];
		arg[2] = 0;
	}
	else
	{
		arg = (char *)malloc(2);
		if (!arg)
			return (1);
		arg[0] = str[i];
		arg[1] = 0;
	}
	new = new_token(arg, 0, type_token);
	(*token) = lst_add_back_token((*token), new);
	return (0);
}

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

t_token	*new_token(char *str, int flag, int type_token)
{
	t_token *token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (0);
	token->str = str;
	token->temp = ft_strdup(str);
	if (type_token != WORD)
		token->temp = 0;
	token->check_var = 0;
	token->inner_join = 0;
	token->type_token = type_token;
	token->flag = flag;
	token->prev = 0;
	token->next = 0;
	return (token);
}

t_token	*lst_add_back_token(t_token *token, t_token *new_token)
{
	t_token *tmp;

	tmp = token;
	if (!tmp)
		return (new_token);
	if(tmp && new_token)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token;
		new_token->prev = tmp;
	}
	return (token);
}

//it's possible to free all value token here, to check if it's necessary
t_token	*lst_del_token(t_token *token)
{
	t_token *tmp;

	tmp = token->next;
	free(token->temp);
	free(token);
	return (tmp);
}

void lst_clear_all_token(t_token *token)
{
	while (token)
		token = lst_del_token(token);
}


int token_word(t_token **token, char *str, int i, int start)
{
	int j;
	char *arg;
	t_token *new;

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
	new = new_token(arg, WORD, 0);
	(*token) = lst_add_back_token((*token), new);
	return (0);
}

int token_other(t_token **token, char *str, int i, int type_token)
{
	char *arg;
	t_token *new;

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
	new = new_token(arg, type_token, 0);
	(*token) = lst_add_back_token((*token), new);
	return (0);
}
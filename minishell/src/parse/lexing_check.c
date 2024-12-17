/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:30:17 by vrandria          #+#    #+#             */
/*   Updated: 2024/12/17 08:58:14 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_token	*def_var_on_token(t_token *token)
{
	t_token	*tmp;
	char	*str;

	tmp = token;
	if (tmp->type_token == PIPE)
	{
		str = ft_strdup("syntax error near unexpected token\'|\'");
		token->exit_value = print_error(str, NULL, 2);
		free(str);
		return (token);
	}
	while (tmp->next != 0)
	{
		tmp = var_check(tmp);
		tmp = check_double(tmp);
		if (tmp->exit_value == 2)
		{
			token->exit_value = 2;
			return (token);
		}
		tmp = tmp->next;
	}
	token->exit_value = 0;
	return (token);
}

t_token	*var_check(t_token *token)
{
	int	i;

	i = 0;
	if (!token || !token->str)
		return (token);
	while (token->str[i] != '\0')
	{
		if (token->str[i] == '$')
		{
			token->type_token = VAR;
			return (token);
		}
		i++;
	}
	return (token);
}

int	check_double_helpers(t_token *token)
{
	if (token->type_token == PIPE)
	{
		if (token->next->type_token == END)
			return (1);
	}
	else if (token->type_token == APPEND || token->type_token == TRUNC
		|| token->type_token == HEREDOC || token->type_token == INPUT)
	{
		if (token->next->type_token != VAR
			&& token->next->type_token != WORD)
			return (1);
	}
	return (0);
}

t_token	*check_double(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (check_double_helpers(tmp) != 0)
		{
			ft_putstr_fd("syntax error near unexpected token '", 2);
			if (tmp->next->type_token == END)
				ft_putstr_fd("newline", 2);
			else
				ft_putstr_fd(tmp->next->str, 2);
			ft_putstr_fd("'\n", 2);
			token->exit_value = 2;
			return (token);
		}
		tmp = tmp->next;
	}
	token->exit_value = 0;
	return (token);
}

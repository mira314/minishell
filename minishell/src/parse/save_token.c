/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:13:20 by vrandria          #+#    #+#             */
/*   Updated: 2024/09/10 09:13:21 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_token *def_var_on_token(t_token *token)
{
	t_token *tmp;

	tmp = token;
	if (tmp->type_token == PIPE)
	{
		printf("error unexpected value %s\n",tmp->str);
		token->exit_value = FAIL;
		return (token);
	}
	while (tmp)
	{
		tmp = var_check(tmp);
	}
	return (token);
}

t_token *var_check(t_token *token)
{
	int i;

	i = 0;
	while (token->str[i] == 0)
	{
		if (token->str[i] == '$')
		{
			if (token->prev && token->prev->type_token == HEREDOC)
				break ;
			token->type_token = VAR;
			printf("var trouve");
			token = token->next;
			return (token);
		}
		i++;
	}
	token = token->next;
	return (token);
}
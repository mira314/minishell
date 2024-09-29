/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:30:17 by vrandria          #+#    #+#             */
/*   Updated: 2024/09/29 11:19:26 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_token *def_var_on_token(t_token *token)
{
	t_token *tmp;

	tmp = token;
	if (tmp->type_token == PIPE)
	{
        char *str;

        str = "syntax error near unexpected token\'|\'";
		token->exit_value = print_error(str, "", 2);
		return (token);
	}
	while (tmp)
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

t_token *var_check(t_token *token)
{
	int i;

	i = 0;
	while (token->str[i])
	{
		if (token->str[i] == '$')
		{
			if (token->prev && token->prev->type_token == HEREDOC)
				break ;
			token->type_token = VAR;
			return (token);
		}
		i++;
	}
	return (token);
}

int check_double_helpers(t_token *token)
{
    int type;

    type = 0;
    if (token->prev)
    {
        type = token->prev->type_token;
        if (token->type_token == PIPE && type == PIPE)
            return (1);
        if (token->type_token > PIPE && type >= PIPE)
            return (1);
        if (token->type_token == END && type > PIPE)
            return (1);
    }
    return (0);
}

t_token *check_double(t_token *token)
{
    t_token *tmp;
    tmp = token;
    char *msg;

    msg = "syntax error near unexpected token \'newline\'";
    while (tmp)
    {
        if (check_double_helpers(tmp) == 1)
        {
            token->exit_value = print_error(msg, 0, 2);
            return (token);
        }
        tmp = tmp->next;
    }
    token->exit_value = 0;
    return (token);
}

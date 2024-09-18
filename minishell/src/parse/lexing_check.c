/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:30:17 by vrandria          #+#    #+#             */
/*   Updated: 2024/09/18 08:09:34 by vrandria         ###   ########.fr       */
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
        tmp = check_double(tmp);
        if (tmp->exit_value == FAIL)
            {
                token->exit_value = FAIL;
                return (token);
            }
        tmp = tmp->next;
    }
    token->exit_value = SUCCESS;
	return (token);
}

t_token *var_check(t_token *token)
{
	int i;
    t_token *tmp;

	i = 0;
    tmp = token;
	while (token->str[i])
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
	return (tmp);
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
    while(tmp)
    {
        if (check_double_helpers(tmp) == 1)
        {
            printf("syntax error in token (double)\n");
            token->exit_value = FAIL;
            return (token);
        }
        tmp = tmp->next;
    }
    token->exit_value = SUCCESS;
    return (token);
}

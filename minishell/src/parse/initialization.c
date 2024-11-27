/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 07:31:00 by vrandria          #+#    #+#             */
/*   Updated: 2024/11/27 16:17:47 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static t_token	*convert_token(t_data *data, t_token *token)
{
	if (token->type_token == WORD || token->type_token == VAR)
		token = parsins_word(data->cmd, token);
	else if (token->type_token == PIPE)
		token = parsing_pipe(data, token);
	else if (token->type_token == INPUT)
		token = parsing_input(data->cmd, token);
	else if (token->type_token == HEREDOC)
		token = parsing_heredoc(data->cmd, token, data);
	else if (token->type_token == TRUNC)
		token = parsing_trunc(data->cmd, token);
	else if (token->type_token == APPEND)
		token = parsing_append(data->cmd, token);
	return (token);
}

int	init_token(t_data *data, char *input, int flag, int *exit)
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
			start = split_word_and_sep(input, start, data, &i);
		i++;
	}
	if (flag != EMPTY)
	{
		if (flag == DOUBLE_QUOTE || flag == ONE_QUOTE)
		{
			*exit = print_error("error: missing terminating quote", NULL, 2);
			data->exit_value = 1;
			return (1);
		}
	}
	return (0);
}

t_cmd	*init_cmd(t_cmd *cmd)
{
	cmd->output = 0;
	cmd->cmd = 0;
	cmd->args = 0;
	cmd->output = 0;
	cmd->prev = 0;
	cmd->io = 0;
	cmd->next = 0;
	init_input_output(cmd);
	return (cmd);
}

int	fill_cmd(t_data *data, t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->type_token == END)
		return (0);
	while (tmp && tmp->next)
	{
		if (tmp == token)
			data->cmd = lst_add_back_cmd(data->cmd, new_cmd());
		tmp = convert_token(data, tmp);
		if (tmp == NULL)
		{
			data->exit_value = 130;
			return (-1);
		}
		if (tmp->type_token == END)
			break ;
	}
	if (data && data->cmd && data->cmd->cmd != 0)
		data->exit_value = parse_commande(data);
	else
		data->exit_value = 1;
	return (0);
}

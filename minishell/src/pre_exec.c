/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:19:51 by derakoto          #+#    #+#             */
/*   Updated: 2024/12/15 21:32:18 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test(t_token *token)
{
	while (token)
	{
		printf("[%s][%d]\n", token->str, token->type_token);
		token = token->next;
	}
}

t_token	*vars_expander(t_data *data)
{
	t_token	*token;
	t_token	*var_token;
	t_token	*token_tmp;
	t_token	*result;

	var_token = 0;
	token = data->token;
	result = data->token;
	while (token)
	{
		if (token->type_token == VAR || (token->prev != NULL && token->prev->type_token == HEREDOC))
		{
			expand_token_str(data, token);
			split_var_to_token(&var_token, token->str, EMPTY);
			set_tokentype_to_word(var_token);
			result = replace_token(data, var_token, token);
			token_tmp = token;
			token = token->next;
			lst_del_token(token_tmp);
		}
		token = token->next;
	}
	return (result);
}

int	parse_data_input(t_data *data)
{
	int	exit;

	exit = 0;
	if (init_token(data, data->input, 0, &exit) == 1)
		return (1);
	if (exit == 0)
	{
		data->token = def_var_on_token(data->token);
		if (data->token->exit_value != 0)
			exit = data->token->exit_value;
	}
	if (exit == 0)
	{
		data->token = vars_expander(data);
		test(data->token);
		quote_process(data);
		if (fill_cmd(data, data->token) == -1)
			exit = 130;
	}
	return (exit);
}

int	check_only_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 32 || (str[i] < 9 && str[i] > 13))
			return (0);
		i++;
	}
	return (1);
}

int	check_input(t_data *data)
{
	if (ft_strlen(data->input) == 0)
		return (0);
	if (check_only_space(data->input))
		return (0);
	return (1);
}

void	check_g_value(t_data *data)
{
	if (g_last_val != 0)
	{
		data->exit_value = g_last_val;
		g_last_val = 0;
	}
}

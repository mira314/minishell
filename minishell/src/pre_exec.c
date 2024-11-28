/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:19:51 by derakoto          #+#    #+#             */
/*   Updated: 2024/11/27 17:57:48 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		var_process(data, data->token);
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

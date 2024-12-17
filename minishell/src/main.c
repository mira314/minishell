/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:56:40 by vrandria          #+#    #+#             */
/*   Updated: 2024/12/17 09:28:03 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_val = 0;

void	clean_tmp(t_data *data)
{
	data->token = 0;
	free(data->input);
	clear_lst_cmd(data);
}

void	process_input(t_data *data)
{
	int	flag;

	if (ft_strlen(data->input) == 0)
	{
		data->exit_value = 0;
		return ;
	}
	if (check_input(data))
	{
		signal(SIGINT, SIG_IGN);
		flag = parse_data_input(data);
		lst_clear_all_token(data->token);
		if (flag == 0)
			exec(data);
		else
		{
			data->exit_value = flag;
			clear_all_doc(data->cmd);
		}
	}
}

static void	compute_history(t_data *data, char *str)
{
	if (ft_strlen(str) > 0)
	{
		ft_putstr_fd(str, data->history_fd);
		ft_putstr_fd("\n", data->history_fd);
		add_history(str);
	}
}

int	main(int argc, char *argv[], char **env)
{
	t_data	data;

	(void)argc;
	(void)argv;
	if (msh_start_up(&data, env) == 1)
		return (1);
	while (1)
	{
		signal(SIGINT, sig_int_handler);
		signal(SIGQUIT, SIG_IGN);
		data.input = readline("msh$");
		if (data.input == NULL)
			mini_exit(&data, NULL);
		compute_history(&data, data.input);
		if (check_input(&data) == 1)
		{
			check_g_value(&data);
			if (data.input != NULL)
			{
				process_input(&data);
				clean_tmp(&data);
			}
		}
	}
	return (0);
}

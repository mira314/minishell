/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:56:40 by vrandria          #+#    #+#             */
/*   Updated: 2024/12/03 14:35:49 by derakoto         ###   ########.fr       */
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
	if (check_input(data))
	{
		add_history(data->input);
		signal(SIGINT, SIG_IGN);
		data->exit_value = parse_data_input(data);
		lst_clear_all_token(data->token);
		if (data->exit_value == 0)
		{
			exec(data);
			// for(int i = 0; data->cmd->args[i] != NULL; i++)
			// 	printf("%s\n", data->cmd->args[i]);
		}
		else
			clear_all_doc(data->cmd);
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
		data.input = readline("msh$");
		check_g_value(&data);
		if (data.input == NULL)
			mini_exit(&data, NULL);
		process_input(&data);
		clean_tmp(&data);
	}
	return (0);
}

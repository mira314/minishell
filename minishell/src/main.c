/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:56:40 by vrandria          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/10/26 13:28:12 by vrandria         ###   ########.fr       */
=======
<<<<<<< HEAD
/*   Updated: 2024/10/26 12:30:53 by vrandria         ###   ########.fr       */
=======
/*   Updated: 2024/10/26 10:50:51 by derakoto         ###   ########.fr       */
>>>>>>> exec
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_last_val;

int print_token(int token)
{
	if (token ==  WORD)
		printf("[word]");
	if (token == HEREDOC)
		printf("[HEREDOC]");
	if (token ==  VAR)
		printf("[VAR]");
	if (token ==  END)
		printf("[END]");
	if (token ==  PIPE)
		printf("[PIPE]");
	if (token ==  TRUNC)
		printf("[TRUNC]");
	return (0);
}

void test(t_token *test)
{
    while(test)
    {
    printf("[%s]",test->str);
	print_token(test->type_token);
    test = test->next;
	printf("\n");
    }

}

void test_1(t_cmd *cmd)
{
	int i;
	i = 0;

	while (cmd->io->inputs[i].filename != 0)
	{
		printf("input %s\n",cmd->io->inputs[i].filename);
		i++;
	}
}

int parse_data_input(t_data *data)
{
	int exit;

	exit = 0;
	if (init_token(data, data->input, 0)!= 0)
		exit = data->exit_value;
	if (data->exit_value == 0)
	{
		data->token = def_var_on_token(data->token);
		if (data->token->exit_value != 0)
			{
				exit = data->token->exit_value;
				data->exit_value = exit;
			}
			/// to do
		//if (data->exit_value == 0)
			//data->exit_value = check_var(data->token);
	}
	if (data->exit_value == 0)
	{
		var_process(data, data->token);
		fill_cmd(data, data->token);
		test_1(data->cmd);
		//printf("%s" , data->cmd->cmd);
		exec_one_cmd(data);
		//exec_with_redir(data);
	}
		free(data->input);
		//test(data->token);
		lst_clear_all_token(data->token);
		data->token = 0;
	return (exit);
}

int check_only_space(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != 32 || (str[i] < 9 && str[i] > 13))
			return(0);
		i++;
	}
	return (1);
}

int check_input(t_data *data)
{
	if (ft_strlen(data->input) == 0)
		return (0);
	if (check_only_space(data->input))
		return (0);
	return(1);
}

int main(int argc, char *argv[], char **env)
{
	t_data data;

	(void)argc;
	(void)argv;
	
	
	if (msh_start_up(&data, env) == 1)
		return (1);
	while (1)
	{
		data.input = readline("msh$");
		if (data.input == NULL)
			mini_exit(&data);
		data.exit_value = 0;
		if (*data.input && check_input(&data))
		{
			if (data.input)
				add_history(data.input);
			parse_data_input(&data);
		}
		else
			g_last_val = 0;
		clear_lst_cmd(&data);
	}
	return 0;
}

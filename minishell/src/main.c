/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:56:40 by vrandria          #+#    #+#             */
/*   Updated: 2024/09/28 17:28:40 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int print_token(int token)
{
	if (token ==  WORD)
		printf("[word]");
	if (token ==  VAR)
		printf("[VAR]");
	if (token ==  END)
		printf("[END]");
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
int main(int argc, char *argv[], char **env)
{
	(void)argc;
	(void)argv;
	t_data data;
	int exit;
	(void)env;

	exit = 0;
	if(!init_data(&data, env))////vrandria working on it;
		return (1);
	while (1)
	{
		(&data)->input = readline("minishell%");
		data.exit_value = 0;
		if (*data.input)
		{
			if (init_token(&data, (&data)->input, 0)!= 0)
				exit = data.exit_value;
			if (data.exit_value == 0)
				{
					(&data)->token = def_var_on_token((&data)->token);
					if ((&data)->token->exit_value == FAIL)
						return(1);//valeur de return a revoir
				}
			if (data.exit_value == 0)
			{
				var_process(&data, (&data)->token);
				fill_cmd(&data, (&data)->token);
				handles_bultin(&data);
				clear_lst_cmd(&data);
			}
			free((&data)->input);
			//test((&data)->token);
			lst_clear_all_token((&data)->token);
			(&data)->token = 0;
		}
	}
	(void)exit;
	return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:56:40 by vrandria          #+#    #+#             */
/*   Updated: 2024/09/13 13:35:41 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void test(t_token *test)
{
    while(test)
    {
    printf("[%s] [type] %d\n",test->str, test->type_token);
    test = test->next;
    }

}

int main(int argc, char *argv[], char **env)
{
	(void)argc;
	(void)argv;
	t_data data;
	(void)env;

	if(!init_data(&data))////vrandria working on it;
		return (1);
	printf("%s\n","ok for init_data");
	while (1)
	{
		(&data)->input = readline("minishell%");
		if(init_token(&data, (&data)->input, 0))
			return (1);
		(&data)->token = def_var_on_token((&data)->token);
		if ((&data)->token->exit_value == FAIL)
			return(1);
		free((&data)->input);
		test((&data)->token);
		lst_clear_all_token((&data)->token);
		(&data)->token = 0;
	}

	return 0;
}

/*
int main(int argc, char *argv[], char **env)
{
	(void)argc;
	(void)argv;
	t_data data;
	(void)env;

	if(!init_data(&data))////vrandria working on it;
		return (0);
	printf("%s\n","ok for init_data");
	while (1)
	{
		(&data)->input_prompt = readline("minishell%");
		if (is_built_in_cmd((&data)->input) == 1)
			exec_mini_built((&data)->input);
		else
			printf("command not found: %s\n", (&data)->input_prompt);
		free((&data)->input_prompt);
	}
	return 0;
}*/
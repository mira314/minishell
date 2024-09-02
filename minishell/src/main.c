/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:56:40 by vrandria          #+#    #+#             */
/*   Updated: 2024/08/31 15:28:17 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char **env)
{
	(void)argc;
	(void)argv;
	t_data data;
	(void)env;

	if(!init_data(&data))////work on it vrandria
		return (0);
	printf("%s\n","ok for init_data");
	while (1)
	{
		(&data)->input_prompt = readline("minishell%");
		if (is_built_in_cmd((&data)->input_prompt) == 1)
			exec_mini_built((&data)->input_prompt);
		else
			printf("command not found: %s\n", (&data)->input_prompt);
		free((&data)->input_prompt);
	}
	return 0;
}
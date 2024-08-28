/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:56:40 by vrandria          #+#    #+#             */
/*   Updated: 2024/08/28 07:34:06 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[])
{
	char *command;
	char *cmd;
	(void)argc;
	while (1)
	{
		printf("minishell%%");
		command = readline(argv[1]);
		if (is_built_in_cmd(cmd) == 1)
			exec_mini_built(cmd);
		else
			printf("command not found: %s\n", cmd);
		free(command);
		free(cmd);
	}
	return 0;
}
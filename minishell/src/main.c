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
	char *cmd;
	(void)argc;
	(void)argv;
	while (1)
	{
		printf("minishell%%");
		cmd = readline(argv[1]);
		if (is_built_in_cmd(cmd) == 1)
			exec_mini_built(cmd);
		else
			printf("command not found: %s\n", cmd);
		free(cmd);
	}
	return 0;
}
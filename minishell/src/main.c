/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 10:56:40 by vrandria          #+#    #+#             */
/*   Updated: 2024/08/24 11:20:47 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[])
{
	char *command;
	(void)argc;
	ft_printf("%s\n","test");
	while (1)
	{
		printf("minishell%%");
		command = readline(argv[1]);
		//printf("la commande est ->%s\n", command);
		free(command);
	}
	return 0;
}
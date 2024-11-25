/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 05:44:51 by derakoto          #+#    #+#             */
/*   Updated: 2024/11/25 05:45:13 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_echo(char **args)
{
	int	i;
	int	nl;

	if (*args == 0)
	{
		write(1, "\n", 1);
		return (0);
	}
	i = 0;
	nl = ft_strncmp(args[0], "-n", 3);
	if (nl == 0)
		i = 1;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1] != 0)
			printf(" ");
		i++;
	}
	if (nl)
		printf("\n");
	return (0);
}

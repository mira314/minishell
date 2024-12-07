/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 05:44:51 by derakoto          #+#    #+#             */
/*   Updated: 2024/12/07 11:42:32 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	parse_option(char *option, int *nl)
{
	int	i;

	if (option == NULL)
		return (-1);
	if (option[0] == '-')
	{
		i = 1;
		while (option[i] != 0)
		{
			if (option[i] != 'n')
				return (-1);
			i++;
		}
		if (i != 1 && option[i] == '\0')
		{
			*nl = 0;
			return (0);
		}
	}
	return (-1);
}

int	treat_options(char **args, int *nl)
{
	int	result;

	if (args == NULL)
		return (0);
	result = 0;
	*nl = 1;
	while (args[result] != NULL && parse_option(args[result], nl) == 0)
		result ++;
	return (result);
}

int	ft_echo(char **args)
{
	int	i;
	int	nl;

	if (*args == 0)
	{
		write(1, "\n", 1);
		return (0);
	}
	i = treat_options(args, &nl);
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i] && args[i + 1] != 0)
			printf(" ");
		i++;
	}
	if (nl)
		printf("\n");
	return (0);
}

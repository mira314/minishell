/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:25:50 by derakoto          #+#    #+#             */
/*   Updated: 2024/10/12 14:26:28 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	cd_to_home(void)
{
	char	*pwd;

	pwd = getenv("HOME");
	if (pwd != 0)
		return (chdir(pwd));
	return (1);
}
/*
	should update env_var
*/
int	mini_cd(char **args)
{
	int	arg_len;

	errno = 0;
	if (args == NULL)
		return (cd_to_home());
	arg_len = mini_tbl_len(args);
	if (arg_len > 2)
	{
		print_error(args[0], "too many arguments", 1);
		return (1);
	}
	if (arg_len < 2)
		return (cd_to_home());
	if (ft_strlen(args[1]) == 0)
		return (cd_to_home());
	return (chdir(args[1]));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 06:01:02 by derakoto          #+#    #+#             */
/*   Updated: 2024/11/25 06:01:03 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_env_key(char *env, char *str)
{
	int	i;

	if (env == NULL || str == NULL)
		return (-1);
	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == '=' || str[i] != env[i])
			return (-1);
		i++;
	}
	if (env[i] == '=' || env[i] == 0)
		return (0);
	return (-1);
}

int	mini_unset(char **o_env, char **env)
{
	int	i;

	if (env == NULL || o_env == NULL)
		return (1);
	i = 0;
	while (env[i] != 0)
	{
		unset_one_env(o_env, env[i]);
		i++;
	}
	return (0);
}

void	unset_one_env(char **o_env, char *env)
{
	int	i;

	if (o_env == NULL || env == NULL)
		return ;
	i = 0;
	while (o_env[i] != 0)
	{
		if (is_env_key(o_env[i], env) == 0)
		{
			free(o_env[i]);
			while (o_env[i + 1] != 0)
			{
				o_env[i] = o_env[i + 1];
				i++;
			}
			o_env[i] = 0;
			break ;
		}
		i++;
	}
}

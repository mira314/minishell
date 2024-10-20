/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:31:09 by derakoto          #+#    #+#             */
/*   Updated: 2024/10/20 09:39:05 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	env_key_len(char *env)
{
	int	len;

	len = 0;
	if (env == 0)
		return (-1);
	while (env[len] != '=' && env[len] != 0)
		len++;
	return (len);
}

int	is_same_key(char *env1, char *env2)
{
	int	env1_key_len;
	int	i;

	env1_key_len = env_key_len(env1);
	if (env_key_len(env2) != env1_key_len)
		return (1);
	i = 0;
	while (i < env1_key_len)
	{
		if (env1[i] != env2[i])
			return (1);
		i++;
	}
	return (0);
}

int	is_value_present(char *env)
{
	size_t	i;

	if (env == 0)
		return (-1);
	i = 0;
	while (env[i] != 0)
	{
		if (env[i] == '=')
			return (0);
		i++;
	}
	return (-1);
}

int	is_key_env_valid(char *key)
{
	int	i;

	if (key == NULL)
		return (-1);
	if (env_key_len(key) == 0)
		return (-1);
	if (ft_isdigit(key[0]) == 1)
		return (-1);
	i = 0;
	while (key[i] != 0 && key[i] != '=')
	{
		if (ft_isalnum(key[i]) == 0)
			return (-1);
		i++;
	}
	return (0);
}

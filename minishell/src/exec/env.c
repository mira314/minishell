/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:43:58 by derakoto          #+#    #+#             */
/*   Updated: 2024/10/20 05:03:20 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	**dup_env(char **f_env)
{
	char	**result;
	size_t	size;
	size_t	i;

	if (f_env == NULL)
		return (NULL);
	size = mini_tbl_len(f_env);
	result = (char **)malloc(sizeof(char *) * (size + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (f_env[i] != 0)
	{
		result[i] = ft_strdup(f_env[i]);
		i++;
	}
	result[i] = 0;
	return (result);
}

char	**try_update(char **o_env, char *env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (o_env[i] != 0)
	{
		if (is_same_key(env, o_env[i]) == 0)
		{
			if (is_value_present(env) == 0)
			{
				tmp = ft_strdup(env);
				if (tmp == 0)
					return (o_env);
				free(o_env[i]);
				o_env[i] = tmp;
			}
			return (o_env);
		}
		i++;
	}
	return (0);
}

char *get_env_value(char **envs, char *key)
{
	int	i;

	if (envs == NULL || key == NULL)
		return (NULL);
	i = 0;
	while (envs[i] != 0)
	{
		if (is_env_key(envs[i], key) == 0)
			return (ft_strdup(envs[i] + env_key_len(envs[i]) + 1));
		i++;
	}
	return (NULL);
}

char *get_env(char **envs, char *key)
{
	int	i;

	if (envs == NULL || key == NULL)
		return (NULL);
	i = 0;
	while (envs[i] != 0)
	{
		if (is_env_key(envs[i], key) == 0)
			return (ft_strdup(envs[i]));
		i++;
	}
	return (NULL);
}

int	is_key_of(char *key, char *env)
{
	int	key_len;
	int	i;

	if (key == NULL || env == NULL)
		return (-1);
	key_len = ft_strlen(key);
	if (key_len != env_key_len(env))
		return (1);
	i = 0;
	while (i < key_len)
	{
		if (key[i] != env[i])
			return (1);
		i++;
	}
	return (0);
}

int		mini_env(char **args, char **envs)
{
	int	i;

	if (args == NULL)
		return (1);
	if (mini_tbl_len(args) > 1)
	{
		print_error(args[0], ": too many arguments", 1);
		return (1);
	}
	if (envs == NULL)
		return (1);
	i = 0;
	while (envs[i] != 0)
	{
		printf("%s\n", envs[i]);
		i++;
	}
	return (0);
}
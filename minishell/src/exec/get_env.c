/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:43:58 by derakoto          #+#    #+#             */
/*   Updated: 2024/12/02 04:19:29 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_env_unset(char **envs, char *key)
{
	int	i;

	if (envs == NULL)
		return (0);
	if (key == NULL)
		return (1);
	i = 0;
	while (envs[i] != 0)
	{
		if (is_env_key(envs[i], key) == 0)
			return (1);
		i++;
	}
	return (0);
}

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

char	*get_env_value(char **envs, char *key)
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

char	*get_env(char **envs, char *key)
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

int	mini_env(char **args, char **envs)
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
		if (is_value_present(envs[i]) == 0)
			printf("%s\n", envs[i]);
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 05:37:52 by derakoto          #+#    #+#             */
/*   Updated: 2024/11/26 06:02:13 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	**add_env(char **o_env, char **n_env, int *status)
{
	size_t	i;
	char	**result;

	result = o_env;
	i = 0;
	while (n_env[i] != 0)
	{
		if (is_key_env_valid(n_env[i]) != 0)
		{
			ft_putstr_fd("export: \"", 2);
			ft_putstr_fd(n_env[i], 2);
			ft_putstr_fd("\" : invalid key\n", 2);
			i++;
			if (status != NULL)
				*status = 1;
			continue ;
		}
		if (is_env_duplicated(n_env, i) != 0)
			result = add_one_env(result, n_env[i]);
		i++;
	}
	return (result);
}

char	**add_one_env(char **o_env, char *env)
{
	int		size;
	char	**result;
	int		i;

	if (env == 0 || o_env == 0)
		return (o_env);
	result = try_update(o_env, env);
	if (result != 0)
		return (result);
	size = mini_tbl_len(o_env) + 1;
	result = (char **)malloc(sizeof(char *) * (size + 1));
	if (result == NULL)
		return (o_env);
	i = 0;
	while (o_env[i] != 0)
	{
		result[i] = o_env[i];
		i++;
	}
	result[i] = ft_strdup(env);
	result[i + 1] = 0;
	free(o_env);
	return (result);
}

int	export(char **env)
{
	char	**env_dup;
	int		i;

	env_dup = dup_env(env);
	if (env_dup == 0)
		return (-1);
	sort_env(env_dup);
	i = 0;
	while (env_dup[i] != 0)
	{
		export_one_env(env_dup[i]);
		i++;
	}
	mini_tbl_free(env_dup);
	return (0);
}

void	export_one_env(char *env)
{
	int	i;
	int	key_len;

	key_len = env_key_len(env);
	write(1, "declare -x ", 11);
	i = 0;
	while (env[i] != 0)
	{
		write(1, &env[i], 1);
		if (i == key_len)
			write(1, "\"", 1);
		i++;
	}
	if (is_value_present(env) == 0)
		write(1, "\"", 1);
	write(1, "\n", 1);
}

int	mini_export(char **args, char ***envs)
{
	int	result;

	result = 0;
	if (args == NULL || envs == NULL)
		return (1);
	if (mini_tbl_len(args) == 1)
	{
		export(*envs);
		return (0);
	}
	*envs = add_env(*envs, args + 1, &result);
	return (result);
}

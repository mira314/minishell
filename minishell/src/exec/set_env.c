/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 04:23:33 by derakoto          #+#    #+#             */
/*   Updated: 2024/11/25 04:25:25 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

char	**update_env(char **o_env, char *env)
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
	return (o_env);
}

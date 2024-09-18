/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:43:58 by derakoto          #+#    #+#             */
/*   Updated: 2024/09/18 15:09:21 by derakoto         ###   ########.fr       */
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
	size = ft_tbllen(f_env);
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


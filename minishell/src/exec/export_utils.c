/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 05:37:16 by derakoto          #+#    #+#             */
/*   Updated: 2024/11/25 05:37:32 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	int	i;

	if (str1 == NULL || str2 == NULL)
		return (-1);
	i = 0;
	while (str1[i] != 0)
	{
		if (str1[i] != str2[i])
			return ((unsigned int)str1[i] - (unsigned int)str2[i]);
		i++;
	}
	return ((unsigned int)str1[i] - (unsigned int)str2[i]);
}

void	sort_env(char **env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (env[i + 1] != NULL)
	{
		j = i + 1;
		while (env[j] != NULL)
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	is_env_duplicated(char **envs, int index)
{
	int	i;

	if (envs == 0)
		return (-1);
	i = 1;
	while (envs[index] != 0 && envs[index + i] != 0)
	{
		if (is_same_key(envs[index], envs[index + i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

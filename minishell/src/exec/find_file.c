/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 05:39:34 by derakoto          #+#    #+#             */
/*   Updated: 2024/12/08 11:18:24 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_file_in(char *path, char *file_name)
{
	DIR				*directory;
	struct dirent	*elem;

	if (path == NULL || file_name == NULL)
		return (-1);
	directory = opendir(path);
	if (directory == NULL)
		return (-1);
	while (1)
	{
		elem = readdir(directory);
		if (elem == NULL)
			break ;
		if (ft_strncmp(elem->d_name, file_name, ft_strlen(file_name) + 1) == 0)
		{
			closedir(directory);
			return (0);
		}
	}
	closedir(directory);
	return (1);
}

char	*is_in_path_env(char *file_name, char **envs)
{
	char	*path;
	char	**splitted_path;
	int		i;
	char	*result;

	path = get_env_value(envs, "PATH");
	if (path == NULL)
		return (NULL);
	splitted_path = ft_split(path, ':');
	free(path);
	if (splitted_path == NULL)
		return (NULL);
	i = 0;
	while (splitted_path[i] != 0)
	{
		if (is_file_in(splitted_path[i], file_name) == 0)
		{
			result = ft_strdup(splitted_path[i]);
			mini_tbl_free(splitted_path);
			return (result);
		}
		i++;
	}
	mini_tbl_free(splitted_path);
	return (NULL);
}

char	*build_path(char *path, char *file_name)
{
	char	*result;
	char	*temp;

	if (path == NULL || file_name == NULL)
		return (NULL);
	temp = ft_strjoin(path, "/");
	if (temp == NULL)
		return (NULL);
	result = ft_strjoin(temp, file_name);
	free(temp);
	return (result);
}

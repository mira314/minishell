/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:25:50 by derakoto          #+#    #+#             */
/*   Updated: 2024/12/03 05:30:55 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	update_pwd_env(t_data	*data)
{
	char	*pwd_val;
	char	*old_pwd;
	char	*new_pwd;
	char	pwd_buffer[PWD_MAX_LEN];

	pwd_val = get_env_value(data->env, "PWD");
	if (pwd_val != NULL)
	{
		old_pwd = ft_strjoin("OLDPWD=", pwd_val);
		free(pwd_val);
		if (old_pwd != NULL)
		{
			data->env = update_env(data->env, old_pwd);
			free(old_pwd);
		}
	}
	if (getcwd(pwd_buffer, PWD_MAX_LEN) == NULL)
		return ;
	new_pwd = ft_strjoin("PWD=", pwd_buffer);
	if (new_pwd == NULL)
		return ;
	data->env = update_env(data->env, new_pwd);
	free(new_pwd);
}

static int	cd_to_home(t_data *data)
{
	char	*pwd;
	int		result;

	pwd = get_env_value(data->env, "HOME");
	if (pwd != 0)
	{
		result = chdir(pwd);
		if (result == -1)
		{
			ft_putstr_fd("cd: ", STDERR_FILENO);
			perror(pwd);
			free(pwd);
			return (1);
		}
		free(pwd);
		update_pwd_env(data);
		return (0);
	}
	ft_putstr_fd("cd: \"HOME\" is undefined\n", 2);
	return (1);
}

int	chdir_with_cdpath(char **env, char *path)
{
	char	*cd_path;
	char	*path_joinned;
	int		result;

	path_joinned = path;
	cd_path = get_env_value(env, "CDPATH");
	if (cd_path != NULL)
	{
		path_joinned = ft_strjoin(cd_path, path);
		free(cd_path);
		if (path_joinned == NULL)
			return (1);
		printf("%s\n", path_joinned);
		result = chdir(path_joinned);
		free(path_joinned);
		if (result == -1)
		result = chdir(path);
	}
	else
		result = chdir(path_joinned);
	return (result);
}

int	mini_cd(t_data *data, t_cmd *cmd)
{
	int		arg_len;
	int		result;
	char	**args;

	args = cmd->args;
	arg_len = mini_tbl_len(args);
	if (arg_len > 2)
	{
		print_error(args[0], ": too many arguments", 1);
		return (1);
	}
	if (arg_len == 1)
		return (cd_to_home(data));
	if (arg_len == 2 && ft_strlen(args[1]) == 0)
		return (0);
	result = chdir_with_cdpath(data->env, args[1]);
	if (result == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		perror(args[1]);
		return (1);
	}
	update_pwd_env(data);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:25:50 by derakoto          #+#    #+#             */
/*   Updated: 2024/12/11 09:46:08 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	update_old_pwd(t_data *data, char *pwd_val)
{
	char	*old_pwd;
	char	*prev_old;

	if (pwd_val == NULL)
		pwd_val = get_env_value(data->var, "PWD");
	if (pwd_val == NULL)
		old_pwd = ft_strdup("OLDPWD=");
	else
		old_pwd = ft_strjoin("OLDPWD=", pwd_val);
	free(pwd_val);
	prev_old = get_env_value(data->env, "OLDPWD");
	if (prev_old == NULL)
		data->var = add_one_env(data->var, old_pwd);
	else
		data->env = add_one_env(data->env, old_pwd);
	free(old_pwd);
	free(prev_old);
}

static void	update_pwd_env(t_data *data)
{
	char	*pwd_val;
	char	*new_pwd;
	char	pwd_buffer[PWD_MAX_LEN];

	if (getcwd(pwd_buffer, PWD_MAX_LEN) == NULL)
		return ;
	new_pwd = ft_strjoin("PWD=", pwd_buffer);
	if (new_pwd == NULL)
		return ;
	pwd_val = get_env_value(data->env, "PWD");
	update_old_pwd(data, pwd_val);
	pwd_val = get_env_value(data->env, "PWD");
	if (pwd_val != NULL)
		data->env = add_one_env(data->env, new_pwd);
	else
		data->var = add_one_env(data->var, new_pwd);
	free(pwd_val);
	free(new_pwd);
}

static int	cd_to_home(t_data *data)
{
	char	*pwd;
	int		result;

	pwd = get_env_value(data->env, "HOME");
	if (pwd != 0)
	{
		if (ft_strlen(pwd) == 0)
			return (0);
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

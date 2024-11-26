/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:25:50 by derakoto          #+#    #+#             */
/*   Updated: 2024/11/26 05:56:21 by derakoto         ###   ########.fr       */
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

int	mini_cd(t_data *data, t_cmd *cmd)
{
	int		arg_len;
	int		result;
	char	**args;

	args = cmd->args;
	if (args == NULL)
		return (cd_to_home(data));
	arg_len = mini_tbl_len(args);
	if (arg_len > 2)
	{
		print_error(args[0], ": too many arguments", 1);
		return (1);
	}
	if (arg_len < 2 || ft_strlen(args[1]) == 0)
		return (cd_to_home(data));
	result = chdir(args[1]);
	if (result == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		perror(args[1]);
		return (1);
	}
	update_pwd_env(data);
	return (0);
}

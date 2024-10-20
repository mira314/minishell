/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:25:50 by derakoto          #+#    #+#             */
/*   Updated: 2024/10/20 04:35:22 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	cd_to_home(void)
{
	char	*pwd;

	pwd = getenv("HOME");
	if (pwd != 0)
		return (chdir(pwd));
	return (1);
}
/*
	should update env_var
*/
static void update_pwd_env(t_data	*data)
{
	char	*pwd_val;
	char	*old_pwd;
	char	*new_pwd;
	char	pwd_buffer[PWD_MAX_LEN];

	pwd_val = get_env_value(data->env, "PWD");
	if (pwd_val == NULL)
	{
		ft_putstr_fd("Error Updating PWD env\n", STDERR_FILENO);
		return ;
	}
	old_pwd = ft_strjoin("OLDPWD=",pwd_val);
	free(pwd_val);
	if (old_pwd == NULL)
	{
		ft_putstr_fd("Error Updating PWD env\n", STDERR_FILENO);
		return ;
	}
	data->env = try_update(data->env, old_pwd);
	free(old_pwd);
	if (getcwd(pwd_buffer, PWD_MAX_LEN) == NULL)
		return ;
	new_pwd = ft_strjoin("PWD=", pwd_buffer);
	if (new_pwd == NULL)
		return ;
	data->env = try_update(data->env, new_pwd);
	free(new_pwd);
}
int	mini_cd(t_data *data)
{
	int		arg_len;
	int		result;
	char	**args;

	args = data->cmd->args;
	errno = 0;
	if (args == NULL)
		return (cd_to_home());
	arg_len = mini_tbl_len(args);
	if (arg_len > 2)
	{
		print_error(args[0], ": too many arguments", 1);
		return (1);
	}
	if (arg_len < 2)
		return (cd_to_home());
	if (ft_strlen(args[1]) == 0)
		return (cd_to_home());
	result = chdir(args[1]);
	if (result == -1)
	{
		ft_putstr_fd("cd: ",STDERR_FILENO);
		perror(args[1]);
		return (1);
	}
	update_pwd_env(data);
	return (0);
}

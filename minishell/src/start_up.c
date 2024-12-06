/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 08:55:38 by derakoto          #+#    #+#             */
/*   Updated: 2024/12/06 15:53:07 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define DEFAULT_PATH "PATH=/usr/local/bin:/usr/local/sbin:\
						/usr/bin:/usr/sbin:/bin:/sbin:."

static void	set_pwd(t_data *data)
{
	char	pwd_buffer[200];
	char	*new_pwd;

	if (getcwd(pwd_buffer, 200) == NULL)
		return ;
	new_pwd = ft_strjoin("PWD=", pwd_buffer);
	if (new_pwd == NULL)
		return ;
	data->env = add_one_env(data->env, new_pwd);
	free(new_pwd);
}

int	msh_start_up(t_data *data, char **env)
{
	if (init_data(data, env) == 1)
	{
		ft_putstr_fd("Failed to dup env", STDERR_FILENO);
		return (1);
	}
	set_pwd(data);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_int_handler);
	return (0);
}

int	compute_shell_value(char *str)
{
	int	i;
	int	sign;

	sign = 1;
	if (str == NULL)
		return (0);
	i = 0;
	if (str[0] == '+' || str[0] == '-')
	{
		i = 1;
		if (str[1] == '\0')
			return (0);
	}
	if (str[0] == '-')
		sign = -1;
	while (str[i] != '\0')
	{
		if (!isdigit(str[i]))
			return (0);
		i++;
	}
	if (sign == -1)
		return (-1);
	return (ft_atoi(str));
}

char	**update_shell_level(char **env)
{
	char	*value;
	char	*tmp;
	int		int_value;

	if (env == NULL)
		return (NULL);
	value = get_env_value(env, "SHLVL");
	if (value == NULL)
		int_value = 1;
	else
	{
		int_value = compute_shell_value(value) + 1;
		free(value);
	}
	value = ft_itoa(int_value);
	if (value == NULL)
		return (env);
	tmp = ft_strjoin("SHLVL=", value);
	free(value);
	if (tmp == NULL)
		return (env);
	env = add_one_env(env, tmp);
	free(tmp);
	return (env);
}

int	init_data(t_data *data, char **env)
{
	data->var = NULL;
	data->var = (char **)malloc(sizeof(char *));
	if (data->var == NULL)
		return (1);
	*data->var = NULL;
	if (is_env_unset(env, "PATH") == 0)
		data->var = add_one_env(data->var, DEFAULT_PATH);
	data->input = 0;
	data->cmd = 0;
	data->token = 0;
	data->exit_value = 0;
	data->env = dup_env(env);
	if (data->env == NULL)
	{
		free(data->var);
		return (1);
	}
	data->env = update_shell_level(data->env);
	g_last_val = 0;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 08:55:38 by derakoto          #+#    #+#             */
/*   Updated: 2024/10/20 10:06:27 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void set_pwd(t_data *data)
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
	signal(SIGQUIT, sig_quit_handler);
}

int	msh_start_up(t_data *data, char **env)
{
	if (init_data(data, env) == 1)
	{
		ft_putstr_fd("Failed to dup env", STDERR_FILENO);
		return (1);
	}
	set_pwd(data);
	return (0);
}

int init_data(t_data *data, char **env)
{
    data->input = 0;
    data->cmd = 0;
    data->token = 0;
    data->exit_value = 1;
    data->env = dup_env(env);
	if (data->env == NULL)
		return (1);
    g_last_val = 0;
    return (0);
}
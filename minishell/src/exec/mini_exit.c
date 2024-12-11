/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 05:19:02 by derakoto          #+#    #+#             */
/*   Updated: 2024/12/11 11:53:28 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	free_and_exit(t_data *data, int exit_code)
{
	mini_tbl_free(data->env);
	mini_tbl_free(data->var);
	clear_lst_cmd(data);
	free(data->input);
	exit(exit_code);
}

static void	print_arg_num_required(t_data *data, char **args)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	free_and_exit(data, 2);
}

int	mini_exit(t_data *data, t_cmd *cmd)
{
	char	**args;
	int		arg_len;

	ft_putstr_fd("exit\n", 2);
	if (data->input != NULL)
	{
		args = cmd->args + cmd->offset;
		arg_len = mini_tbl_len(args);
		if (arg_len >= 2)
		{
			if (mini_is_numeric(args[1]) != 0 || in_long_range(args[1]) == 1)
				print_arg_num_required(data, args);
			else if (arg_len == 2)
				free_and_exit(data, ft_atoi(args[1]));
			ft_putstr_fd("exit: too many arguments\n", 2);
			return (1);
		}
	}
	else
		check_g_value(data);
	free_and_exit(data, data->exit_value);
	return (0);
}

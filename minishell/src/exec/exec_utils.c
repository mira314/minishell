/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 05:12:08 by derakoto          #+#    #+#             */
/*   Updated: 2024/12/17 09:37:52 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	get_error_code(void)
{
	if (errno == EACCES)
		return (126);
	else if (errno == ENOENT)
		return (127);
	else
		return (126);
}

int	get_exitstatus_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		write(1, "\n", 1);
		return (128 + WTERMSIG(status));
	}
	return (0);
}

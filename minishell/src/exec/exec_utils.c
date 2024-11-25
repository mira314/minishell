/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 05:12:08 by derakoto          #+#    #+#             */
/*   Updated: 2024/11/25 06:04:15 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exit_error_code(void)
{
	if (errno == EACCES)
		exit(126);
	else if (errno == ENOENT)
		exit(127);
	else
		exit(126);
}

int	get_exitstatus_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (130);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:42:25 by vrandria          #+#    #+#             */
/*   Updated: 2024/12/18 11:10:05 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static t_token	*wait_and_return_next_token(t_token *token, int fd)
{
	int	status;

	wait(&status);
	close(fd);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 130)
			return (NULL);
	}
	token = decide_next_token(token);
	return (token);
}

t_token	*parsing_heredoc(t_cmd *cmd, t_token *token, t_data *data)
{
	int		fd;
	int		pid;
	char	*tmp;

	tmp = token->next->temp;
	token->next->temp = trim_delim_heredoc(tmp, cmd);
	fd = prepare_heredoc_file(cmd);
	if (fd == -1)
		return (NULL);
	pid = fork();
	if (pid == -1)
		return (NULL);
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
		get_doc(data, cmd, token, fd);
	else
		token = wait_and_return_next_token(token, fd);
	return (token);
}

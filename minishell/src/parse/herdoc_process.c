/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:42:25 by vrandria          #+#    #+#             */
/*   Updated: 2024/12/17 12:15:51 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_token	*parsing_heredoc(t_cmd *cmd, t_token *token, t_data *data)
{
	int		fd;
	int		pid;
	int		status;
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
	{
		wait(&status);
		close(fd);
		if (WIFSIGNALED(status))
			return (NULL);
		token = decide_next_token(token);
	}
	return (token);
}

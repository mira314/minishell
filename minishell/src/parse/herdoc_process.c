/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:42:25 by vrandria          #+#    #+#             */
/*   Updated: 2024/11/27 15:47:19 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_input	*add_input(t_cmd *cmd, char *filename, int mode)
{
	int		i;
	int		count;
	t_input	*tmp;
	t_input	*new;

	i = 0;
	count = 0;
	tmp = cmd->io->inputs;
	while (tmp[i].filename)
		i++;
	new = malloc((sizeof(t_input) * (i + 2)));
	if (!new)
		return (NULL);
	while (count < i)
	{
		new[count].filename = tmp[count].filename;
		new[count].mode = tmp[count].mode;
		count++;
	}
	new[count].filename = filename;
	new[count].mode = mode;
	new[count + 1].filename = NULL;
	free(tmp);
	return (new);
}

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

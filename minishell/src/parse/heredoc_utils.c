/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:44:45 by derakoto          #+#    #+#             */
/*   Updated: 2024/11/27 15:47:26 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*trim_delim_heredoc(char *del, t_cmd *cmd)
{
	int		i;
	int		j;
	char	*new;

	new = malloc (sizeof(char) * ft_strlen(del) + 1);
	if (!new)
		return (0);
	i = 0;
	j = 0;
	while (del[i])
	{
		if (del[i] == 34 || del[i] == 39)
		{
			cmd->io->quote_status = 1;
			i++;
		}
		else
			new[j++] = del[i++];
	}
	new[j] = 0;
	free(del);
	return (new);
}

t_token	*decide_next_token(t_token *token)
{
	if (token->next->next)
		token = token->next->next;
	else
		token = token->next;
	return (token);
}

void	clear_doc(t_input *inputs)
{
	int	i;

	if (inputs == 0)
		return ;
	i = 0;
	while (inputs[i].filename != NULL)
	{
		if (inputs[i].mode == HEREDOC)
		{
			if (unlink(inputs[i].filename) == -1)
				perror("Heredoc deletetion");
		}
		i++;
	}
}

void	clear_all_doc(t_cmd *top_cmd)
{
	t_cmd	*cmd;

	cmd = top_cmd;
	while (cmd)
	{
		clear_doc(cmd->io->inputs);
		cmd = cmd->next;
	}
}
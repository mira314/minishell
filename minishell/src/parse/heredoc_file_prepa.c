/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_file_prepa.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:50:54 by derakoto          #+#    #+#             */
/*   Updated: 2024/12/08 05:10:02 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*create_file_name(char *path)
{
	char	*file_name;
	int		i;
	int		index_to_change;

	file_name = (char *)malloc(sizeof(char) * 10);
	if (file_name == NULL)
		return (NULL);
	file_name[0] = '.';
	i = 1;
	while (i < 9)
		file_name[i++] = 'a';
	file_name[i] = 0;
	index_to_change = 1;
	while (is_file_in(path, file_name) == 0)
	{
		file_name[index_to_change]++;
		if (file_name[index_to_change] == 'z')
			index_to_change++;
		if (index_to_change == 9)
		{
			free(file_name);
			return (NULL);
		}
	}
	return (file_name);
}

int	prepare_heredoc_file(t_cmd *cmd)
{
	int		result_fd;
	char	*file_name;

	file_name = create_file_name(".");
	if (file_name == NULL)
	{
		printf("An error occured\n");
		return (-1);
	}
	result_fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (result_fd != -1)
	{
		while (cmd->next)
			cmd = cmd->next;
		cmd->io->outputs = add_output(cmd, file_name, HEREDOC);
		free(file_name);
	}
	else
		free(file_name);
	return (result_fd);
}

void	get_doc_content(t_data *data, t_cmd *cmd, t_token *token, int fd)
{
	char	*str;
	char	*tmp;

	while (1)
	{
		write(1, ">", 1);
		str = get_next_line(0);
		if (str == NULL)
		{
			printf("There is an error\n");
			break ;
		}
		if (is_delimiter(token->next->temp, str) == 0)
			break ;
		tmp = str;
		if (cmd->io->quote_status == 0 && ft_strrchr(str, '$') != 0)
			str = var_str_heredoc(data, tmp, 0);
		write(fd, str, ft_strlen(str));
		free(str);
	}
	free(str);
}

void	get_doc(t_data *data, t_cmd *cmd, t_token *token, int fd)
{
	signal(SIGINT, SIG_DFL);
	get_doc_content(data, cmd, token, fd);
	close(fd);
	lst_clear_all_token(data->token);
	free_and_exit(data, 0);
}

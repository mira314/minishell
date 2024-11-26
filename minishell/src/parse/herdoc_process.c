/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:42:25 by vrandria          #+#    #+#             */
/*   Updated: 2024/11/26 10:14:29 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	size_str_not_var(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (ft_isalpha((int)str[i]) == 0)
			break ;
		i++;
	}
	return (i);
}

char	*herdoc_var_handl(t_data *data, char *str)
{
	char	*exit_val;
	char	*var;
	int		size;

	var = get_type_var(str, 0);
	if (var && ft_varchr(data, var) != 0)
	{
		size = ft_strlen(var);
		if (ft_varchr(data, var) == 1)
			exit_val = get_var_var(data, var, size);
		else if (ft_varchr(data, var) == 2)
			exit_val = get_var_env(data, var, size);
	}
	else if (var && var[0] == '?' && var[1] == '=')
		exit_val =  ft_itoa(data->exit_value);
	else
		exit_val = 0;
	free(var);
	return (exit_val);   
}

char	*var_convert_her(char *str, char *var)
{
	char	*new;

	if (!str)
		str = ft_strdup("");
	new = ft_strjoin(str, var);
	free(var);
	free(str);
	return (new);
}

char	*var_str_heredoc(t_data *data, char *str, int i)
{
	char	*get_var;
	char	*tmp;
	char	*join;
	char	tab[2];

	tab[1] = 0;
	join = 0;
	tmp = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$' && sep_next_char(str[i + 1] == 0))
		{
			get_var = herdoc_var_handl(data, &str[i]);
			free(tmp);
			tmp = var_convert_her(join, get_var);
			i += size_str_not_var(&str[i]);
		}
		else
		{
			tab[0] = str[i];
			join = ft_strjoin(tmp, tab);
			free(tmp);
			tmp = join;
			i++;
		}
	}
	free(tmp);
	return (join);
}

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
	return(new);
}

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
	{
		file_name[i] = 'a';
		i++;
	}
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

t_token	*parsing_heredoc(t_cmd *cmd, t_token *token, t_data *data)
{
	char	*file;
	int		fd;
	char	*str;
	int		pid;
	int		status;
	char	*tmp;

	tmp = token->next->temp;
	token->next->temp = trim_delim_heredoc(tmp, cmd);
	file = create_file_name(".");
	if(file == NULL)
	{
		printf("An error occured\n");
		return (NULL);
	}
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		free(file);
		return (NULL);
	}
	pid = fork();
	if (pid == -1)
		return (NULL);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		while (1)
		{
			write(1, ">", 1);
			str = get_next_line(0);
			if (str == NULL)
			{
				printf("There is an error\n");
				break;
			}
			if (is_delimiter(token->next->temp, str) == 0)
				break;
			tmp = str;
			if (cmd->io->quote_status == 0 && ft_strrchr(str, '$') != 0)
				str = var_str_heredoc(data, tmp, 0);
			write(fd, str, ft_strlen(str));
			free(str);
		}
		close(fd);
		free(file);
		lst_clear_all_token(data->token);
		free_and_exit(data, 0);
	}
	else
	{
		wait(&status);
		close(fd);
		while (cmd->next)
			cmd = cmd->next;
		cmd->io->inputs = add_input(cmd, file, HEREDOC);
		if (WIFSIGNALED(status))
			return (NULL);
		if (token->next->next)
			token = token->next->next;
		else
			token = token->next;
	}
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

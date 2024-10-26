#include "parse.h"

char	**add_str_to_table(char	**tbl, char	*str)
{
	char	**result;
	int		i;
	int		size;

	if (tbl == NULL || str == NULL)
		return (tbl);
	size = ft_tbllen(tbl) + 1;
	result = (char **)malloc(sizeof(char*) * (size + 1));
	if (result == NULL)
		return (tbl);
	i = 0;
	while (tbl[i] != 0)
	{
		result[i] = tbl[i];
		i++;
	}
	result[i] = str;
	result[i + 1] = NULL;
	free(tbl);
	return (result);
}

int	get_token_size(char	*str_cmd, int quote_count, int *i)
{
	int		size;
	
	*i = 0;
	size = 0;
	quote_count = 0;
	if (str_cmd == NULL)
		return (-1);
	while (str_cmd[*i] == ' ' && str_cmd[*i] != 0)
		*i += 1;
	while (str_cmd[*i] != 0)
	{
		if (str_cmd[*i] == '"')
			quote_count++;
		else
		{
			if (str_cmd[*i] == ' ' && (quote_count % 2) == 0)
				break ;
			size++;
		}
		*i += 1;
	}
	return (size);
}

char	*get_token_value(char *str_cmd, int size)
{
	char	*result;
	int		i;
	int		token_index;

	result = (char *)malloc(sizeof(char) * (size + 1));
	if(result == NULL)
		return (NULL);
	i = 0;
	while (str_cmd[i] == ' ' && str_cmd[i] != 0)
		i++;
	token_index = 0;
	while (str_cmd[i] != 0 && token_index < size)
	{
		if (str_cmd[i] != '"')
			result[token_index++] = str_cmd[i];
		i++;
	}
	result[size] = 0;
	return (result);
}

int	init_cmd(t_command *cmd)
{
	cmd->args = (char**)malloc(sizeof(char*));
	cmd->input = (char**)malloc(sizeof(char*));
	cmd->output = (char**)malloc(sizeof(char*));
	if (cmd->args == NULL || cmd->input == NULL || cmd->output == NULL)
		return (-1);
	*cmd->args = NULL;
	*cmd->input = NULL;
	*cmd->output = NULL;
	return (0);
}

void	destroy_cmd(t_command *cmd)
{
	ft_tbl_free(cmd->args);
	ft_tbl_free(cmd->input);
	ft_tbl_free(cmd->output);
}
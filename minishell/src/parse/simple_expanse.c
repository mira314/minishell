
#include "parse.h"

char *add_quote_handel(char *str, char *tmp, int flag)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			tmp[j] = 39;
			tmp[j + 1] = str[i];
			j++;
			flag = 1;
		}
		else
		{
			tmp[j] = str[i];
			if (ft_isalpha(str[i + 1]) == 0 && flag == 1)
				{
					tmp[j+1] = 39;
					j++;
					flag = 0;
				}
		}
		j++;
		i++;
	}
	tmp[j + 1] = 0;
	return (tmp);
}

char *add_quote(char *str)
{
	char *tmp;
	int i;
	int var;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			var++;
		i++;
	}
	tmp = malloc(sizeof(char) * (ft_strlen(str) + (var * 2) + 1) );
	if (!tmp)
		return (0);
	tmp = add_quote_handel(str, tmp, 0);
	free(str);
	return (tmp);
}

char	*simple_var_handl(t_data *data, char *str)
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
		if (ft_strchr(exit_val, '$'))
			exit_val = add_quote(exit_val);
	}
	else
		exit_val = ft_strdup("");
	free(var);
	return (exit_val);
}

char *process_simple_var(t_data *data, char *str, int *i)
{
	char	*get_var;
	char	*tmp;
	char	*join;

	tmp = 0;
	join = 0;
	while (str[*i] && str[*i] != 39)
	{
		if (str[*i] == '$' && sep_next_char(str[*i + 1] == 0))
		{
			get_var = simple_var_handl(data, &str[*i]);
			tmp = var_convert_her(join, get_var);
			*i += size_str_not_var(&str[*i]);
			break ; 
		}
		else
		{
			join = append_char_to_str(tmp, str[*i]);
			tmp = join;
			(*i)++;
		}
	}
	return (tmp);
}

void remplace_simple_var(t_data *data, int i, int flag)
{
	char *str;
	char *tmp;
	int	j;
	char *var;

	str = data->input;
	while (str[i])
	{
		flag = check_quote(flag, str[i]);
		if (flag == EMPTY && str[i] == '$' && ft_isalpha(str[i + 1]))
		{
			j = i;
			tmp = process_simple_var(data, str, &i);
			str[j] = 0;
			var = ft_strjoin(str, tmp);
			str = ft_strjoin(var, &str[i]);
			i = -1;
		}
		i++;
	}
    data->input = str;
}

int	expand_simple_var(t_data * data)
{
	if (ft_strchr(data->input, '$') == 0)
		return (1);
	remplace_simple_var(data, 0, EMPTY);
    if (ft_strlen(data->input) > 1)
        return (1);
    return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 14:52:53 by derakoto          #+#    #+#             */
/*   Updated: 2024/11/29 09:05:25 by vrandria         ###   ########.fr       */
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
		exit_val = ft_itoa(data->exit_value);
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

char	*append_char_to_str(char *tmp, char c)
{
	char	tab[2];
	char	*str;

	tab[1] = 0;
	tab[0] = c;
	if (tmp == 0)
		tmp = ft_strdup("");
	str = ft_strjoin(tmp, tab);
	free(tmp);
	return (str);
}

char	*var_str_heredoc(t_data *data, char *str, int i)
{
	char	*get_var;
	char	*tmp;
	char	*join;

	tmp = 0;
	join = 0;
	while (str[i])
	{
		if (str[i] == '$' && sep_next_char(str[i + 1] == 0))
		{
			get_var = herdoc_var_handl(data, &str[i]);
			tmp = var_convert_her(join, get_var);
			i += size_str_not_var(&str[i]);
		}
		else
		{
			join = append_char_to_str(tmp, str[i]);
			tmp = join;
			i++;
		}
	}
	return (join);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:46:11 by derakoto          #+#    #+#             */
/*   Updated: 2024/12/06 07:07:56 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	destroy_var(t_var *var)
{
	if (var == NULL)
		return ;
	free(var->value);
	free(var->name);
	free(var);
}

t_var	*build_var(t_data *data, char *str, int name_len, int *i)
{
	t_var	*result;
	int		j;

	result = (t_var *)malloc(sizeof(t_var));
	if (result == NULL)
		return (NULL);
	result->index = *i - 1;
	result->name_len = name_len;
	result->name = (char *)malloc(sizeof(char) * (name_len + 1));
	j = 0;
	while (j < name_len)
	{
		result->name[j] = str[j];
		j++;
	}
	result->name[j] = '\0';
	if (str[0] == '?')
		result->value = ft_itoa(data->exit_value);
	else if (ft_isdigit(str[0]) || name_len == 0)
		result->value = NULL;
	else
		result->value = get_env_value(data->var, result->name);
	if (result->value == NULL)
		result->value = get_env_value(data->env, result->name);
	return (result);
}

t_var	*new_var(t_data *data, char *str, int *i, int flag)
{
	int		name_len;
	int		j;
	t_var	*result;

	name_len = 0;
	j = 0;
	if (str[j] == '?' || ft_isdigit(str[j]))
	{
		name_len = 1;
		j = j + 1;
	}
	else if (ft_isalnum(str[j]) || str[j] == '_')
	{
		while (ft_isalnum(str[j]) || str[j] == '_')
		{
			name_len++;
			j = j + 1;
		}
	}
	else if (str[j] == '\0' || str[j] == ' ' || str[j] == '+' || (is_quote(str[j]) == flag) || (flag != EMPTY && is_quote(str[j])))
		return (NULL);
	result = build_var(data, str, name_len, i);
	*i = *i + j;
	return (result);
}

t_var	**add_var(t_var **var, t_var *var_to_add)
{
	int		var_count;
	t_var	**new_var;
	int		i;

	var_count = 0;
	if (var == NULL)
		return (0);
	while (var[var_count] != NULL)
		var_count++;
	new_var = (t_var **)malloc(sizeof(t_var *) * (var_count + 2));
	if (new_var == NULL)
		return (NULL);
	i = 0;
	while (i < var_count)
	{
		new_var[i] = var[i];
		i++;
	}
	new_var[i++] = var_to_add;
	new_var[i] = NULL;
	free(var);
	return (new_var);
}

void	take_all_vars(t_data *data, char *str, t_var ***var)
{
	int		i;
	int		quote;
	t_var	*var_tmp;
	int		flag;

	flag = EMPTY;
	i = 0;
	while (str[i] != 0)
	{
		quote = is_quote(str[i]);
		if (quote != EMPTY)
			handle_quote(str, &flag, &i, quote);
		else if (str[i] == '$')
		{
			i++;
			var_tmp = new_var(data, str + i, &i, flag);
			if (var_tmp)
				*var = add_var(*var, var_tmp);
		}
		else if (str[i] == '<')
			handle_less_sign(str, &i);
		else
			i++;
	}
}

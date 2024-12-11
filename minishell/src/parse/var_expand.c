/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:44:39 by derakoto          #+#    #+#             */
/*   Updated: 2024/12/11 10:37:52 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_var	**identify_var(t_data *data, char *str)
{
	t_var	**var;

	var = (t_var **)malloc(sizeof(t_var *));
	if (var == NULL)
		return (NULL);
	var[0] = NULL;
	if (data == NULL || str == NULL)
		return (NULL);
	take_all_vars(data, str, &var);
	return (var);
}

int	compute_new_input_len(t_var **var, char *str)
{
	int	new_input_len;
	int	vars_name_len;
	int	values_len;
	int	i;

	vars_name_len = 0;
	values_len = 0;
	i = 0;
	while (var[i])
	{
		vars_name_len += var[i]->name_len + 1;
		if (var[i]->value != NULL)
			values_len += ft_strlen(var[i]->value);
		i++;
	}
	new_input_len = ft_strlen(str) - vars_name_len + values_len;
	return (new_input_len);
}

char	*build_new_input(t_var **var, char *str, char *new_input)
{
	int	x;
	int	y;
	int	z;
	int	m;

	x = 0;
	y = 0;
	z = 0;
	while (var[x] != NULL)
	{
		while (y != var[x]->index)
			new_input[z++] = str[y++];
		y += var[x]->name_len + 1;
		if (var[x]->value)
		{
			m = 0;
			while (var[x]->value[m] != '\0')
				new_input[z++] = var[x]->value[m++];
		}
		x++;
	}
	while (str[y] != '\0')
		new_input[z++] = str[y++];
	new_input[z] = 0;
	return (new_input);
}

char	*var_expand(t_data *data, char *str)
{
	char	*new_input;
	t_var	**var;
	int		new_input_len;
	int		i;

	new_input = str;
	var = identify_var(data, str);
	if (var == NULL)
		return (str);
	if (var[0] != NULL)
	{
		new_input_len = compute_new_input_len(var, str);
		new_input = (char *)malloc(sizeof(char) * (new_input_len + 1));
		if (new_input == NULL)
			return (NULL);
		build_new_input(var, str, new_input);
		free(str);
		i = 0;
		while (var[i] != NULL)
			destroy_var(var[i++]);
	}
	free(var);
	return (new_input);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_identify_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:38:26 by derakoto          #+#    #+#             */
/*   Updated: 2024/12/14 21:28:21 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	handle_quote(char *str, int *flag, int *i, int quote)
{
	if (quote == EMPTY)
		return ;
	if (*flag == EMPTY)
		*flag = quote;
	else if (*flag == quote)
		*flag = EMPTY;
	*i = *i + 1;
	if (*flag == ONE_QUOTE)
	{
		while (str[*i] != '\'' && str[*i] != '\0')
			*i = *i + 1;
		if (str[*i] != '\0')
		{
			*flag = EMPTY;
			*i = *i + 1;
		}
	}
}

void	handle_less_sign(t_data *data, char *str, t_var ***var)
{
	t_var	*var_tmp;
	int		flag;
	int		i;

	flag = EMPTY;
	i = 0;
	while (str[i] == ' ')
		i = i + 1;
	while (str[i] != ' ' && str[i] != '\0')
	{
		handle_quote(str, &flag, &i, is_quote(str[i]));
		if (str[i] == '$' && is_quote(str[i + 1]) != EMPTY && !flag)
		{
			printf("%d %d\n", flag, i);
			i = i + 1;
			var_tmp = new_var(data, str + i, &i, flag);
			if (var_tmp)
				*var = add_var(*var, var_tmp);
		}
		else
			i = i + 1;
	}
}

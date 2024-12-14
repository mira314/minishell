/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_identify_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:38:26 by derakoto          #+#    #+#             */
/*   Updated: 2024/12/14 07:10:14 by derakoto         ###   ########.fr       */
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

void	handle_less_sign(t_data *data, int *i, int flag, t_var ***var)
{
	t_var	*var_tmp;
	char	*str;

	str = data->input;
	*i = *i + 1;
	if (str[*i] == '<')
	{
		*i = *i + 1;
		while (str[*i] == ' ')
			*i = *i + 1;
		while (str[*i] != ' ' && str[*i] != '\0')
		{
			handle_quote(str, &flag, i, is_quote(str[*i]));
			if (str[*i] == '$' && is_quote(str[*i + 1]) != EMPTY && !flag)
			{
				printf("%d %d\n", flag, *i);
				*i = *i + 1;
				var_tmp = new_var(data, str + *i, i, flag);
				if (var_tmp)
					*var = add_var(*var, var_tmp);
			}
			else
				*i = *i + 1;
		}
	}
}

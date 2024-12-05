/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_identify_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 19:38:26 by derakoto          #+#    #+#             */
/*   Updated: 2024/12/05 19:42:13 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	handle_quote(char *str, int *flag, int *i, int quote)
{
	if (*flag == EMPTY)
		*flag = quote;
	else if (*flag == quote)
		*flag = EMPTY;
	*i = *i + 1;
	if (*flag == ONE_QUOTE)
	{
		while (str[*i] != '\'')
			*i = *i + 1;
		*flag = EMPTY;
		*i = *i + 1;
	}
}

void	handle_less_sign(char *str, int *i)
{
	*i = *i + 1;
	if (str[*i] == '<')
	{
		*i = *i + 1;
		while (str[*i] == ' ')
			*i = *i + 1;
		while (str[*i] != ' ' && str[*i] != '\0')
			*i = *i + 1;
	}
}

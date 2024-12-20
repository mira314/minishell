/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 05:45:19 by derakoto          #+#    #+#             */
/*   Updated: 2024/11/25 05:45:24 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_pwd(void)
{
	char	pwd_buffer[100];

	if (getcwd(pwd_buffer, 100) != NULL)
		printf("%s\n", pwd_buffer);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 08:13:10 by vrandria          #+#    #+#             */
/*   Updated: 2024/08/28 08:20:03 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "minishell.h"

typedef struct s_token
{
    char *str;
    char *temp;
    int *check_var;
    int type_token;
    struct s_token *prev;
    struct s_token *next;
} t_token;

typedef struct s_data
{
    char **env;
    char    *input_prompt;
} t_data;

#endif

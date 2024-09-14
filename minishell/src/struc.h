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
    int check_var;
    int type_token;
    int flag;
    int inner_join;
    int exit_value;
    struct s_token *prev;
    struct s_token *next;
} t_token;

typedef struct s_cmd
{
    char *cmd;
    char **args;
    char *history;
    int output;
    struct s_cmd *prev;
    struct s_cmd *next;
}t_cmd;

typedef struct s_data
{
    char **env;
    char    *input;
    t_cmd   *cmd;
    t_token *token;
} t_data;

#endif

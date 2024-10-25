/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 08:13:10 by vrandria          #+#    #+#             */
/*   Updated: 2024/10/25 05:20:56 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "minishell.h"

typedef struct s_file
{
    struct s_file *next;
    char *file;
} t_file;

typedef struct s_io_fd
{
    t_file *input_file;
    t_file *output_file;
    int input_fd;
    int output_fd;
    int stdin;
    int stdout;
    char *delim_heredoc;
    int quote_status;
}t_io_fd;

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
    t_io_fd *io;
    struct s_cmd *prev;
    struct s_cmd *next;
}t_cmd;

typedef struct s_data
{
    char **env;
    char    *input;
    t_cmd   *cmd;
    t_token *token;
    int exit_value;
} t_data;

#endif

/****** suggestion */

/*typedef struct s_input
{
    int mode;
    char    *filename;
}   t_input;

typedef struct s_output
{
    int mode;
    char    *filename;
}   t_output;

typedef struct s_cmd
{
    char        *cmd;
    char        **args;
    t_input     *inputs;
    t_output    *outputs; 
}t_cmd;
*/

/********************/
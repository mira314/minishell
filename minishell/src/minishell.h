/* ************************************************************************** */
/*                                    data                                        */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 13:32:50 by vrandria          #+#    #+#             */
/*   Updated: 2024/09/03 11:14:14 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "struc.h"
# include "../lib/libft/libft.h"
# include "parse/parse.h"
# include "exec/exec.h"
# include <stdio.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <errno.h>

extern int g_last_val;

# define EMPTY 0
# define SPACES 1
# define WORD 2
# define VAR 3
# define TRUNC 6
# define INPUT 5
# define HEREDOC 7
# define APPEND 8
# define PIPE 4
# define END 9
# define ONE_QUOTE 11
# define DOUBLE_QUOTE 12
# define FAIL 1
# define SUCCESS 0


/***************utils.c*********************** */
int print_error(char *str, char *msg, int code);

/****************clear.c  ******************* */
void clean_cmd(t_data *data);
#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 13:32:50 by vrandria          #+#    #+#             */
/*   Updated: 2024/12/17 11:21:58 by derakoto         ###   ########.fr       */
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
# include <signal.h>

extern int	g_last_val;

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
int		print_error(char *str, char *msg, int code);

/****************clear.c  ******************* */
int		main(int argc, char *argv[], char **env);
int		check_input(t_data *data);
void	clear_tab(char **env);
int		msh_start_up(t_data *data, char **env);
int		check_only_space(char *str);
int		parse_data_input(t_data *data);
void	check_g_value(t_data *data);
void	sig_int_handler(int sig_num);
void	child_sigint_handler(int sig_num);
void	load_history(int fd_history);
void	set_tokentype_to_word(t_token *token);
t_token	*replace_token(t_data *data, t_token *var_token, t_token *token);
void	expand_token_str(t_data *data, t_token *token);
t_token	*skip_token(t_token *token, t_token	*result);
t_data	*static_data(t_data *data);

#endif

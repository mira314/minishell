/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 10:30:04 by vrandria          #+#    #+#             */
/*   Updated: 2024/09/23 08:44:37 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PARSE_H
# define PARSE_H

# include "../../src/minishell.h"

/*************mini_commande_parse.c**************/
int is_built_in_cmd(char *cmd);
void exec_mini_built(char *cmd);
/************token.c***************************/
char *ft_strtok(char *str, const char *delim);
/*************parse_prompt_input ********/
int parse_from_prompt(t_data *data);
/**************initialisation************** */
int init_data(t_data *data);
int init_token(t_data *data, char *input, int flag);
t_cmd *init_cmd(t_cmd *cmd);
void fill_cmd(t_data *data, t_token *token);
/*****token.c***************************/
int token_split_word_and_sep(char *str, int start, t_data *data, int *i);
int what_is_sep(char *str, int i);
int check_quote(int flag, int input);

/******************lst_token_utils.c   ******************************/

t_token	*new_token(char *str, int flag, int type_token);

t_token	*lst_add_back_token(t_token *token, t_token *new_token);
t_token	*lst_del_token(t_token *token);
void lst_clear_all_token(t_token *token);
/******************lexing_check.c***********************************/
t_token *def_var_on_token(t_token *token);
t_token *var_check(t_token *token);
t_token *check_double(t_token *token);
int check_double_helpers(t_token *token);
/**************************save_token.c */
int token_word(t_token **token, char *str, int i, int start);
int token_other(t_token **token, char *str, int i, int type_token);
/*******************parsing.c **********************************/
t_token *parsins_word(t_cmd *cmd, t_token *token);
/*********************lst_cmd_utils.c************************ */
t_cmd *new_cmd(void);
t_cmd *lst_add_back_cmd(t_cmd *cmd, t_cmd *new_cmd);
/*********************split_args.c *************************** */
t_token *split_args(t_token *token, t_cmd *cmd);
t_token *ft_split_echo(t_token *token, t_cmd *cmd);
#endif


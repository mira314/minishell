/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 10:30:04 by vrandria          #+#    #+#             */
/*   Updated: 2024/10/19 09:04:44 by vrandria         ###   ########.fr       */
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
int init_data(t_data *data, char **env);
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
t_token *echo_parsing_arg(t_token *token, t_cmd *cmd);
/*********************lst_cmd_utils.c************************ */
t_cmd *new_cmd(void);
t_cmd *lst_add_back_cmd(t_cmd *cmd, t_cmd *new_cmd);
void clear_lst_cmd(t_data *data);
/*********************split_args.c *************************** */
t_token *split_args(t_token *token, t_cmd *cmd);
int arg_count(t_token *token);
t_token *ft_split_echo(t_token *token, t_cmd *cmd);
char **ft_split_expansion(int len, t_token *token, t_cmd *cmd, char **tab);
char **copy_new_tab(int len, char **str, t_token *token, t_cmd *cmd);
/*******************mini_commande_pars.c***********************/
int parse_commande(t_data *data);
int handles_bultin(t_data *data);
/******************var_processing.c***********************/
int var_process(t_data *data, t_token *token);
t_token *statu_quote_token(t_token *token, int c);
int sep_next_char(char c);
int double_quote_is_close(char *str, int i);
/*************var_proces_utils.c********************** */
int ft_varchr(t_data *data, char *str);
char *get_var_env(t_data *data, char *str, int size_var);
char *exit_var_value(t_data *data, t_token *token, char *str);

/*************var_proces_utils_2.c********************** */
char *get_type_var(char *var, int start);
int is_correct_type_var(char c);
int size_var(char *var);
int sub_var_replace(t_token *token, char *str_new, char *str, int i);

/*************var_proces_utils_2.c********************** */
int sub_var(t_token *token, char *str, int i, int size);
t_token *var_conversion(t_token *token, char *str, int i);
int var_copy(char *dest, char *src, int i);
char *get_str_token(char *str, char *str_new, int size, int i);
/********************split_args_other.c*********************/
int count_word(t_token *token);
t_token *new_args_for_other_cmd(t_token *token , t_cmd *cmd);
t_token *add_args_for_other_cmd(t_token *token, t_cmd *cmd);
/********************pipe_process*********************** */
t_token *parsing_pipe(t_data *data, t_token *token);
/********************input_process*********************** */
t_token *parsing_input(t_cmd *cmd, t_token *token);
#endif


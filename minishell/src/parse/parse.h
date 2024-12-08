/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 10:30:04 by vrandria          #+#    #+#             */
/*   Updated: 2024/12/08 06:58:33 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../../src/minishell.h"

/*************mini_commande_parse.c**************/
int			is_built_in_cmd(char *cmd);
void		exec_mini_built(char *cmd);
/************token.c***************************/
char		*ft_strtok(char *str, const char *delim);
/*************parse_prompt_input ********/
int			parse_from_prompt(t_data *data);
/**************initialisation************** */
int			init_data(t_data *data, char **env);
int			init_token(t_data *data, char *input, int flag, int *exit);
t_cmd		*init_cmd(t_cmd *cmd);
int			fill_cmd(t_data *data, t_token *token);
/***********init_int_and_out.c *************************************/
t_output	*init_output(t_output **output);
void		init_input_output(t_cmd *cmd);
/***********token.c*************************************************/
int			split_word_and_sep(char *str, int start, t_data *data, int *i);
int			what_is_sep(char *str, int i);
int			check_quote(int flag, int input);
/******************lst_token_utils.c******************************/
t_token		*new_token(char *str, int flag, int type_token);
t_token		*lst_add_back_token(t_token *token, t_token *new_token);
t_token		*lst_del_token(t_token *token);
void		lst_clear_all_token(t_token *token);
/******************lexing_check.c***********************************/
t_token		*def_var_on_token(t_token *token);
t_token		*var_check(t_token *token);
t_token		*check_double(t_token *token);
int			check_double_helpers(t_token *token);
/**************************save_token.c */
int			token_word(t_token **token, char *str, int i, int start);
int			token_other(t_token **token, char *str, int i, int type_token);
/*******************parsing.c **********************************/
void		split_token(t_cmd *cmd, t_token *token);
t_token		*parsins_word(t_cmd *cmd, t_token *token);
char		*adding_var(t_token **token_ptr);
t_token		*echo_parsing_arg(t_token *token, t_cmd *cmd);
/*********************lst_cmd_utils1.c************************ */
void		clear_lst_cmd(t_data *data);
void		clear_outputs(t_output *output);
void		clear_io(t_io_fd *io);
/*********************lst_cmd_utils.c************************ */
t_cmd		*new_cmd(void);
t_cmd		*lst_add_back_cmd(t_cmd *cmd, t_cmd *new_cmd);
/*********************split_args.c *************************** */
t_token		*split_args(t_token *token, t_cmd *cmd);
t_token		*combin_var(t_token *token, char **var);
t_token		*ft_split_echo(t_token *token, t_cmd *cmd);
char		**split_expansion(int len, t_token *token, t_cmd *cmd, char **tab);
char		**copy_new_tab(int len, char **str, t_token *token, t_cmd *cmd);
/*******************mini_commande_pars.c***********************/
int			parse_commande(t_data *data);
int			handles_bultin(t_data *data, t_cmd *cmd, int *exit_status);
/******************var_processing.c***********************/
int			var_process(t_data *data, t_token *token, int count);
t_token		*statu_quote_token(t_token *token, int c);
int			double_quote_is_close(char *str, int i);
/*************var_proces_utils.c********************** */
int			ft_varchr(t_data *data, char *str);
char		*get_var_var(t_data *data, char *str, int size_var);
char		*get_var_env(t_data *data, char *str, int size_var);
char		*exit_var_value(t_data *data, t_token *token, char *str);
/*************var_proces_utils_2.c********************** */
char		*get_type_var(char *var, int start);
int			is_correct_type_var(char c);
int			size_var(char *var);
int			sub_var_replace(t_token *token, char *str_new, char *str, int i);
/*************var_proces_utils_2.c********************** */
int			sub_var(t_token *token, char *str, int i, int size);
t_token		*var_conversion(t_token *token, char *str, int i);
int			var_copy(char *dest, char *src, int i);
char		*get_str_token(char *str, char *str_new, int size, int i);
int			sep_next_char(char c);
/********************split_args_other.c*********************/
int			count_word(t_token *token);
int			arg_count(t_token *token);
t_token		*args_other_cmd(t_token *token, t_cmd *cmd, int i, t_token *tmp);
t_token		*add_args_for_other_cmd(t_token *token, t_cmd *cmd);
/********************pipe_process*********************** */
t_token		*parsing_pipe(t_data *data, t_token *token);
/********************input_process*********************** */
t_token		*parsing_input(t_cmd *cmd, t_token *token);
/********************trunc_process.c*********************** */
t_token		*parsing_trunc(t_cmd *cmd, t_token *token);
/***********************herdoc_process.c  *************** */
t_token		*parsing_heredoc(t_cmd *cmd, t_token *token, t_data *data);
char		*herdoc_var(t_data *data, char *str);
void		clear_doc(t_output *inputs);
void		clear_all_doc(t_cmd *top_cmd);
/**********************append_process.c ******************/
t_token		*parsing_append(t_cmd *cmd, t_token *token);
/*********************quote_process**********************/
void		quote_process(t_data *data);
t_token		*trim_quote(t_token *token, int j);
int			switch_flag_token(int i, t_token *token);
int			switch_flag_token_empty(int *i, t_token *token);
/***************quote_process_utils.c  **************** */
int			check_quote_flag(t_token *token, int i);
int			switch_flag_token(int i, t_token *token);
t_output	*add_output(t_cmd *cmd, char *filename, int mode);
char		*create_file_name(char *path);
int			prepare_heredoc_file(t_cmd *cmd);
void		get_doc_content(t_data *data, t_cmd *cmd, t_token *token, int fd);
void		get_doc(t_data *data, t_cmd *cmd, t_token *token, int fd);
int			size_str_not_var(char *str);
char		*herdoc_var_handl(t_data *data, char *str);
char		*var_convert_her(char *str, char *var);
char		*var_str_heredoc(t_data *data, char *str, int i);
char		*trim_delim_heredoc(char *del, t_cmd *cmd);
t_token		*decide_next_token(t_token *token);
/***************hedeco_var********************************* */
char		*append_char_to_str(char *tmp, char c);
int			expand_simple_var(t_data *data);
int			is_quote(char c);
int			compute_new_input_len(t_var **var, char *str);
char		*build_new_input(t_var **var, char *str, char *new_input);
char		*var_expand(t_data *data, char *str);
void		destroy_var(t_var *var);
t_var		*build_var(t_data *data, char *str, int name_len, int *i);
t_var		*new_var(t_data *data, char *str, int *i, int flag);
t_var		**add_var(t_var **var, t_var *var_to_add);
t_var		**identify_var(t_data *data, char *str);
void		handle_quote(char *str, int *flag, int *i, int quote);
void		handle_less_sign(char *str, int *i);
void		take_all_vars(t_data *data, char *str, t_var ***var);

#endif

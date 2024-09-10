/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 10:30:04 by vrandria          #+#    #+#             */
/*   Updated: 2024/09/10 08:50:04 by vrandria         ###   ########.fr       */
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
/*****token.c***************************/
int token_split_word_and_sep(char *str, int start, t_data *data, int i);
int what_is_sep(char *str, int i);
int check_quote(int flag, int input);
#endif


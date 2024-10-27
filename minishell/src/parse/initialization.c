/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 07:31:00 by vrandria          #+#    #+#             */
/*   Updated: 2024/10/27 11:16:46 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int init_token(t_data *data, char *input, int flag)
{
    int i;
    int start;
    int limit;

    i = 0;
    start = 0;
    limit = ft_strlen(input);
    while (limit >= i)
    {
        flag = check_quote(flag, (int)input[i]);
        if (flag == EMPTY)
            start = token_split_word_and_sep(input, start, data, &i);
        i++;
    }
    if (flag != EMPTY) 
    {
        if (flag == DOUBLE_QUOTE || flag == ONE_QUOTE)
        {
            data->exit_value = print_error("error: missing terminating quote", NULL, 2);
            return(1);
        }
    }
    return (0);
}

t_cmd *init_cmd(t_cmd *cmd)
{
    cmd->cmd = 0;
    cmd->args = 0;
    cmd->output = 0;
    cmd->prev = 0;
    cmd->io = 0;
    cmd->next = 0;
    cmd->history = 0;
    init_input_output(cmd);
    return (cmd);
}

void fill_cmd(t_data *data, t_token *token)
{
    t_token *tmp;

    tmp = token;
    if (tmp->type_token == END)
        return ;
    while (tmp->next)
    {
        if (tmp == token)
            data->cmd = lst_add_back_cmd(data->cmd, new_cmd());
        if (tmp->type_token == WORD || tmp->type_token == VAR)
            tmp = parsins_word(data->cmd, tmp);
        else if (tmp->type_token == PIPE)
            tmp = parsing_pipe(data, tmp);
        else if (tmp->type_token == INPUT)
            tmp = parsing_input(data->cmd, tmp);
        else if (tmp->type_token == TRUNC)
            tmp = parsing_trunc(data->cmd, tmp);
        else if (tmp->type_token == END)
            break ;
        else
        {
            printf("fillcmd %d = %d %s", token->type_token, TRUNC, token->str);
            break ;
        }
    }
    if (data && data->cmd && data->cmd->cmd != 0)
    {
        ft_printf("code not implementeon initialisation\n");
        data->exit_value = parse_commande(data); 
    }
          
    else
        data->exit_value = 1;
}

void init_input_output(t_cmd *cmd)
{
    t_io_fd *io;
    if (cmd->io == 0)
    {
        cmd->io = (t_io_fd *)malloc(sizeof(t_io_fd));
        if (!cmd->io)
            return ;
        io = cmd->io;
        io->inputs = malloc(sizeof(t_input) * 2);
        io->inputs[0].filename = 0;
        io->inputs[1].filename = 0;
        io->outputs = malloc(sizeof(t_output) * 2);
        io->outputs[0].filename = 0;
        io->outputs[1].filename = 0;
        io->input_fd = -1;
        io->output_fd = -1;
        io->stdin = -1;
        io->stdout = -1;
        io->delim_heredoc = 0;
        io->quote_status = 0;
    }
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:42:25 by vrandria          #+#    #+#             */
/*   Updated: 2024/11/18 04:39:30 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void create_file(t_cmd *cmd, char *filename)
{
    cmd->io->inputs[0].filename = filename;
    cmd->io->inputs[0].mode = HEREDOC;
}

static t_input *add_file(t_cmd *cmd, char *filename)
{
    int i;
    int count;
    t_input *tmp;
    t_input *new;

    i = 0;
    count = 0;
    tmp = cmd->io->inputs;
    while (tmp[i].filename)
        i++;
    new = malloc((sizeof(t_input) * (i + 2)));
    if (!new)
        return (0);
    while (count < i)
    {
        new[count].filename = ft_strdup(tmp[count].filename);
        free(tmp[count].filename);
        new[count].mode = tmp[count].mode;
        count++;
    }
        new[count].filename = filename;
        new[count].mode = HEREDOC;
        new[count + 1].filename = 0;
    return (new);
}



char *create_file_name(char *path)
{
    char *file_name;
    int  i;
    int  index_to_change;

    file_name = (char *)malloc(sizeof(char) * 10);
    if (file_name == NULL)
        return (NULL);
    i = 0;
    while (i < 9)
    {
        file_name[i] = 'a';
        i++;
    }
    file_name[i] = 0;
    index_to_change = 0;
    while (is_file_in(path, file_name) == 0)
    {
        file_name[index_to_change]++;
        if (file_name[index_to_change] == 'z')
            index_to_change++;
        if (index_to_change == 9)
        {
            free(file_name);
            return (NULL);
        }
    }
    return (file_name);
}

t_token *parsing_heredoc(t_cmd *cmd, t_token *token)
{
    //t_input *tmp;
    char    *file;
    int     fd;
    char    *str;
    int     pid;
    int     status;
    
    file = create_file_name(".");
    if(file == NULL)
    {
        printf("An error occured\n");
        return (NULL);
    }
    fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        free(file);
        return (NULL);
    }
    pid = fork();
    if (pid == -1)
        return (NULL);
    if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        while (1)
        {
            write(1, ">", 1);
            str = get_next_line(0);
            if (str == NULL)
            {
                printf("There is an error\n");
                break;
            }
            if (is_delimiter(token->next->str, str) == 0)
                break;
            write(fd, str, ft_strlen(str));
            free(str);
        }
        close(fd);
        free(file);
        free(str);
        exit (0);
    }
    else
    {
        wait(&status);
        close(fd);
        if (WIFSIGNALED(status))
            return (NULL);
        //tmp = cmd->io->inputs;
        while (cmd->next)
            cmd = cmd->next;
        if (cmd->io->inputs[0].filename == 0)
            create_file(cmd, file);
        else
        {
            cmd->io->inputs = add_file(cmd, file);
            //free(tmp);
        }
        if (token->next->next)
            token = token->next->next;
        else
            token = token->next;
    }
    return (token);
}

void    clear_doc(t_input *inputs)
{
    int i;

    if (inputs == 0)
        return ;
    i = 0;
    while (inputs[i].filename != NULL)
    {
        if (inputs[i].mode == HEREDOC)
        {
            if (unlink(inputs[i].filename) == -1)
                perror("Heredoc deletetion");
        }
        i++;
    }
}
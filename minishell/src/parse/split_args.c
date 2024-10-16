/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 08:42:40 by vrandria          #+#    #+#             */
/*   Updated: 2024/10/16 08:08:20 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int arg_count(t_token *token)
{
	int count;

	count = 0;
	while (token && (token->type_token == WORD || token->type_token == VAR))
	{
		//les cquote est le variable ne sont pas prise en cmpte pour le moment
		count++;
		token = token->next;
	}
	return (count);
}

t_token *ft_split_echo(t_token *token, t_cmd *cmd)
{
	int len_arg;
	int argc;
	char **result;

	argc = arg_count(token);
	len_arg = 0;
	while (cmd->args[len_arg])
		len_arg++;
	result = (char **)malloc(sizeof(char *) * (argc + len_arg) + 1);
	if (!result)
		return (0);
	result = ft_split_expansion(len_arg, token, cmd, result);
	free(cmd->args);
	cmd->args = 0;
	while (token->type_token || VAR || token->type_token == WORD)
		token = token->next;
	return (token);
}

//creation d autre ficchier pour les autre commande


char **copy_new_tab(int len, char **str, t_token *token, t_cmd *cmd)
{
	int i;

	i = 0;
	while (i < len)
	{
		str[i] = cmd->args[i];
		i++;
	}
	while (token->type_token == WORD || token->type_token == VAR)
	{
		str[i] = ft_strdup(token->str);
		i++;
		token = token->next;
	}
	str[i] = 0;
	return (str);
} 

t_token *split_args(t_token *token, t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd, "echo", 4) == 0)
	{
		if (cmd->args == 0)
		{
			token = echo_parsing_arg(token, cmd);
			return (token);
		}
		else
		{
			token = ft_split_echo(token, cmd);
			return(token);
		}
	}
	else
	{
		if (!cmd->args)
		{
			token = new_args_for_other_cmd(token, cmd);
			return(token);
		}
		else
		{
			token = add_args_for_other_cmd(token, cmd);
			return(token);
		}
		printf("cas non gere -split_args.c\n");
	}
	return (token);
}

char **ft_split_expansion(int len, t_token *token, t_cmd *cmd, char **tab)
{
	int i;

	i = 0;
	while (len > i)
	{
		tab[i] = cmd->args[i];
		i++;
	}
	while (token->type_token == VAR || token->type_token == WORD)
	{
		if (token->inner_join == 1)
		{	
			printf("%s\n", "var non gere sur ft_split_expansion");//////////////////
		}
		else
			tab[i] = ft_strdup(token->str);
		i++;
		token = token->next;
	}
	tab[i] = 0;
	return (tab);
}

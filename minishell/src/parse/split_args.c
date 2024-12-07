/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrandria <vrandria@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 08:42:40 by vrandria          #+#    #+#             */
/*   Updated: 2024/12/07 11:11:35 by vrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_token	*ft_split_echo(t_token *token, t_cmd *cmd)
{
	int		len_arg;
	int		argc;
	char	**result;

	argc = arg_count(token);
	len_arg = 0;
	while (cmd->args[len_arg])
		len_arg++;
	result = (char **)malloc(sizeof(char *) * (argc + len_arg) + 3);
	if (!result)
		return (0);
	result = split_expansion(len_arg, token, cmd, result);
	free(cmd->args);
	cmd->args = result;
	while (token->type_token == VAR || token->type_token == WORD)
		token = token->next;
	return (token);
}

char	**copy_new_tab(int len, char **str, t_token *token, t_cmd *cmd)
{
	int	i;

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

t_token	*split_args(t_token *token, t_cmd *cmd)
{
	if (ft_strncmp(cmd->cmd, "echo", 4) == 0)
	{
		if (cmd->args == 0)
			return (echo_parsing_arg(token, cmd));
		else
			return (ft_split_echo(token, cmd));
	}
	else
	{
		if (!cmd->args)
			return (args_other_cmd(token, cmd, 0, 0));
		else
			return (add_args_for_other_cmd(token, cmd));
	}
	return (token);
}

char	**split_expansion(int len, t_token *token, t_cmd *cmd, char **tab)
{
	int	i;

	i = 0;
	while (len > i)
	{
		tab[i] = cmd->args[i];
		i++;
	}
	while (token->type_token == VAR || token->type_token == WORD)
	{
		tab[i] = ft_strdup(token->str);
		if (token->inner_join == 1)
			token = combin_var(token, &tab[i]);
		i++;
		token = token->next;
	}
	return (tab);
}

t_token	*combin_var(t_token *token, char **var)
{
	char	*tmp;

	tmp = *var;
	while (token->type_token == VAR && token->next->type_token == VAR
		&& token->next->inner_join == 1)
	{
		*var = ft_strjoin(tmp, token->next->str);
		free(tmp);
		token = token->next;
	}
	return (token);
}

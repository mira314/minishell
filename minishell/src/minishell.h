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

# define EMPTY 0
# define WORD 1
# define SPACES 2
# define VAR 3
# define INPUT 4
# define TRUNC 5
# define HEREDOC 6
# define APPEND 8
# define PIPE 9
# define END 10
# define ONE_QUOTE 11
# define DOUBLE_QUOTE 12
# define FAIL 1
# define SUCCES 0

#endif

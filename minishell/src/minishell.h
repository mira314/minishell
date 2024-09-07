/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 13:32:50 by vrandria          #+#    #+#             */
/*   Updated: 2024/09/07 06:02:51 by derakoto         ###   ########.fr       */
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
# define STDOUT 0
# define STDIN 1
# define APPEND 2
# define STDERR 3

typedef struct s_cmd
{
	char	*args;
	char	*input_file;
	char	*output_file;
	int		append;
}	t_cmd;


#endif



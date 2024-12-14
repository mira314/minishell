/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 08:13:10 by vrandria          #+#    #+#             */
/*   Updated: 2024/12/14 07:32:26 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUC_H
# define STRUC_H
# include "minishell.h"

typedef struct s_var
{
	char	*value;
	char	*name;
	int		name_len;
	int		index;
	int		value_len;
}	t_var;

typedef struct s_io_file
{
	int		mode;
	char	*filename;
}	t_io_file;

typedef struct s_io_fd
{
	t_io_file	*outputs;
	int			input_fd;
	int			output_fd;
	int			mode_outputs;
	int			stdin;
	int			stdout;
	int			quote_status;
}	t_io_fd;

typedef struct s_token
{
	char			*str;
	char			*temp;
	int				check_var;
	int				type_token;
	int				flag;
	int				inner_join;
	int				exit_value;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	int				offset;
	char			*history;
	int				output;
	t_io_fd			*io;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_term
{
	int	term_backup;
	int	keybord_backup;
}	t_term;

typedef struct s_data
{
	char	**env;
	char	**var;
	char	*input;
	t_cmd	*cmd;
	t_token	*token;
	int		exit_value;
	t_term	term_backup;
	int		history_fd;
}	t_data;

#endif

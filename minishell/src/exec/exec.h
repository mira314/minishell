/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derakoto <derakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 05:51:35 by derakoto          #+#    #+#             */
/*   Updated: 2024/12/18 10:49:55 by derakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../../src/minishell.h"
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/stat.h>
# define PWD_MAX_LEN 199
# define LONG_MAX_STR "9223372036854775807"
# define LONG_MIN_STR "9223372036854775808"

int		ft_echo(char **args);
int		ft_pwd(void);
int		mini_tbl_len(char **tbl);
void	mini_tbl_free(char **tbl);
int		mini_cd(t_data *data, t_cmd *cmd);
char	**dup_env(char **f_env);
char	**add_env(char **o_env, char **n_env, int *status);
int		env_key_len(char *env);
int		is_same_key(char *env1, char *env2);
int		is_value_present(char *env);
int		is_key_env_valid(char *env);
int		is_env_duplicated(char **envs, int index);
char	**add_one_env(char **o_env, char *env);
char	**try_update(char **o_env, char *env);
void	unset_one_env(char **o_env, char *env);
int		mini_unset(char **o_env, char **env);
int		is_env_key(char *env, char *str);
int		ft_strcmp(const char *str1, const char *str2);
void	sort_env(char **env);
int		export(char **env);
void	export_one_env(char *env);
int		is_key_of(char *key, char *env);
int		is_file_in(char *path, char *file_name);
char	*get_env_value(char **envs, char *key);
char	*get_env(char **envs, char *key);
char	*is_in_path_env(char *file_name, char **envs);
char	*build_path(char *path, char *file_name);
int		exec_one_cmd(t_data *data, t_cmd *cmd);
int		mini_env(char **args, char **envs);
int		mini_export(char **args, char ***envs);
int		mini_exit(t_data *data, t_cmd *cmd);
char	**update_env(char **o_env, char *env);
int		mini_is_numeric(char *str);
int		exec_with_redir(t_data *data, t_cmd *cmd);
int		is_var_assignement(char *str);
int		count_assignement(char **tbl);
int		handle_var(char **tbl, char ***var, int *assign_count);
void	exec(t_data *data);
int		is_delimiter(char *delimiter, char *str);
void	clean_pipes(int **pipes, int size);
void	free_and_exit(t_data *data, int exit_code);
int		handle_redir(t_io_fd *io);
int		redir_output(t_io_file *file, int i);
int		redir_input(t_io_file *file, int i);
int		is_path(char *str);
int		execute_path(t_data *data, t_cmd *cmd, char *path);
int		pipe_loop(t_data *data);
void	close_unused_pipe(int **pipe_fds, int size, int current_index);
int		fork_fun(int **pipes, int i, t_data *data, t_cmd *cmd);
int		exec_with_redir(t_data *data, t_cmd *cmd);
int		exec_with_fork(t_data *data, char *path, char **args, char **envs);
int		get_error_code(void);
int		get_exitstatus_code(int status);
int		execute_tools(t_data *data, t_cmd *cmd, char *path);
void	close_unused_pipe(int **pipe_fds, int size, int current_index);
void	close_one_pipe_fd(int *fds);
void	close_all_pipes(int **pipe_fds, int size);
void	clean_pipes(int **pipes, int size);
int		count_cmd(t_cmd *cmd);
int		**create_pipes(int pipe_count);
int		init_pipes(int **pipe_fds, int size);
int		on_forking_error_pipe(int *fds);
int		fork_and_execute(t_data *data, int **pipe_fds,
			t_cmd *cmd, int cmd_count);
int		is_env_unset(char **envs, char *key);
int		in_long_range(char *str);
int		count_leading_zero(char *str);

#endif

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
# define PWD_MAX_LEN 200

void    exec();
int		ft_echo(char **args);
int	    ft_pwd(void);
int		mini_tbl_len(char **tbl);
void	mini_tbl_free(char **tbl);
int 	mini_cd(t_data *data);
char	**dup_env(char **f_env);
char	**add_env(char **o_env, char **n_env);
int		env_key_len(char *env);
int		is_same_key(char *env1, char *env2);
int		is_value_present(char *env);
int		is_key_env_valid(char *env);
int		is_env_duplicated(char **envs, int index);
char	**add_one_env(char **o_env, char *env);
char	**try_update(char **o_env, char *env);
void    unset_one_env(char **o_env, char *env);
int		mini_unset(char **o_env, char **env);
int		is_env_key(char *env, char *str);
int 	ft_strcmp(const char *str1, const char *str2);
void	sort_env(char **env);
int	    export(char **env);
void	export_one_env(char *env);
int	    is_key_of(char *key, char *env);
int     is_file_in(char *path, char *file_name);
char    *get_env_value(char **envs, char *key);
char	*get_env(char **envs, char *key);
char    *is_in_path_env(char *file_name, char **envs);
char    *build_path(char *path, char *file_name);
int 	exec_one_cmd(t_data *data, t_cmd *cmd);
int		mini_env(char **args, char **envs);
int	    mini_export(char **args, char ***envs);
void    mini_exit(t_data *data, t_cmd *cmd);
char	**update_env(char **o_env, char *env);
int	    mini_is_numeric(char *str);
void	exec_with_redir(t_data *data, t_cmd *cmd);
int     is_var_assignement(char *str);
int     count_assignement(char **tbl);
int     handle_var(char **tbl, char ***var, int *assign_count);
void	exec(t_data *data);
int	    is_delimiter(char *delimiter, char *str);

#endif

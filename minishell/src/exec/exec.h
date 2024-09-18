#ifndef EXEC_H
# define EXEC_H

# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>

int		ft_echo(char **args);
int	    ft_pwd(void);
int		mini_tbl_len(char **tbl);
int		mini_cd(char *path);
char	**dup_env(char **f_env);
char	**add_env(char **o_env, char **n_env);
int		env_key_len(char *env);
int		is_same_key(char *env1, char *env2);
int		env_key_space(char *env);
int		is_value_present(char *env);
int		is_key_env_valid(char *env);
int		is_env_duplicated(char **envs, int index);
char	**add_one_env(char **o_env, char *env);
char	**try_update(char **o_env, char *env);
void    unset_one_env(char **o_env, char *env);
void    unset(char **o_env, char **env);
int		is_env_key(char *env, char *str);
int 	ft_strcmp(const char *str1, const char *str2);
void	sort_env(char **env);
int	    export(char **env);
void	export_one_env(char *env);

#endif


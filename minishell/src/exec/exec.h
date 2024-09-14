#ifndef EXEC_H
# define EXEC_H

# include "../../lib/libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>

int	    ft_echo(char **args);
int 	ft_pwd(void);
int		mini_tbl_len(char **tbl);
int		mini_cd(char *path);
#endif

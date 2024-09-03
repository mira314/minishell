#include "exec.h"

int	mini_tbl_len(char **tbl)
{
	int	i;

	i = 0;
	while (tbl[i] != 0)
		i++;
	return (i);
}
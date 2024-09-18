#include "exec.h"

int	mini_tbl_len(char **tbl)
{
	int	i;

	i = 0;
	while (tbl[i] != 0)
		i++;
	return (i);
}

void	mini_tbl_free(char **tbl)
{
	int	i;

	if (tbl == 0)
		return ;
	i = 0;
	while (tbl[i] != 0)
	{
		free(tbl[i]);
		i++;
	}
	free(tbl[i]);
	free(tbl);
}
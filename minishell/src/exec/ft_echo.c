#include "exec.h"

void	ft_echo(char **args)
{
	int	i;
    int	nl;

	if (args == 0)
		exit(EXIT_SUCCESS);
	i = 0;
	nl = ft_strncmp(args[0], "-n", 3);
	if (nl == 0)
		i = 1;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1] != 0)
			printf(" ");
		i++;
	}
	if (nl)
		printf("\n");
}

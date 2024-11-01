#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

char	*str;

int	main(void)
{
	str = malloc(sizeof(char));
	if (fork() == 0)
	{
		*str = 'A';
		exit(0);
	}
	else
	{
		wait(NULL);
		sleep(1);
		free(str);
	}
	return(0);
}

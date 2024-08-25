#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int	g_i;

int	main(void)
{
	g_i = 6;
	if (fork() == 0)
	{
		printf("%d\n", g_i);
		g_i ++;
		printf("%d\n", g_i);
	}
	else
	{
		sleep(1);
		printf("%d\n", g_i);
	}
}

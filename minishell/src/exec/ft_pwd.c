#include "exec.h"

int	ft_pwd(void)
{
	char	pwd_buffer[100];

	if (getcwd(pwd_buffer, 100) != NULL)
		printf("%s\n", pwd_buffer);
	return (0);
}

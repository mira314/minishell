#include "exec.h"

void	ft_pwd(void)
{
	char	pwd_buffer[100];

	if (getcwd(pwd_buffer, 100) != NULL)
		printf("%s\n", pwd_buffer);
}

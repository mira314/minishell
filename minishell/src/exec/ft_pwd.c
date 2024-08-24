#include "exec.h"

void ft_pwd(void)
{
    char *pwd;

    pwd = getenv("PWD");
    if(pwd != 0)
        printf("%s\n", pwd);
}
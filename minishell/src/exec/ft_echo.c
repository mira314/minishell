#include "exec.h"

void ft_echo(char *str, int n_option)
{
    printf("%s", str);
    if(n_option == 0)
        printf("\n");
}

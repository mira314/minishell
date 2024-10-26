#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
    char    str[]="Bonjour 42\n";
    int     fd[2];
    char    buffer_out[100];
    int     n_read;
    int     pid;
    if(pipe(fd) == -1)
    {
        perror("Piping");
        return (0);
    }
    write(fd[0], str, strlen(str));
    n_read = read(fd[1], buffer_out, 99);
    buffer_out[n_read] = 0;
    printf("%s", buffer_out);
    close(fd[0]);
    close(fd[1]);
    return (0);
}
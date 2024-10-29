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
    write(fd[1], str, strlen(str));
    close(fd[1]);
    n_read = read(fd[0], buffer_out, 99);
    close(fd[0]);
    buffer_out[n_read] = 0;
    printf("%s\n", buffer_out);
    return (0);
}
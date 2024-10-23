#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int    pipe_loop(char **str, int i)
{
    int     fd[2];
    int     pid;
    int     print[2];

    if (pipe(fd) == -1)
    {
        perror("piping");
        return (1);
    }
    pid = fork();
    if (pid == -1)
    {
        perror("Forking");
        close(fd[1]);
        close(fd[2]);
        return (1);
    }
    if (pid == 0)
    {
        sleep(i);
        printf("PROCESS %d : %s\n", i, str[0]);
        exit(0);
    }
    else
    {
        if (str[1] != 0)
            pipe_loop(str + 1, i + 1);
        wait(NULL);
        write(1,"parent ", 7);
        print[0] = i + 0x30;
        write(1, print, 1);
        write(1, "\n", 1);
    }
}

int main(void)
{
    char    *str[]={"Bonjour", "les etudiants", "de 42", "Mlay", "Galaxy", "Andraharo",NULL};

    pipe_loop(str, 0);
    return (0);
}
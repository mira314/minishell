#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
    char    *command[]={"./minishell",NULL};
    int     pid;

    pid = fork();
    if (pid == -1)
    {
        perror("Forking");
        return (0);
    }
    if (pid == 0)
    {
        execve(command[0], command, NULL);
        perror("Error");
        exit(EXIT_FAILURE);
    }
    else{
        wait(NULL);
    }
    return (0);
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int    pipe_loop(char ***cmds, int i, int *input)
{
    int     output[2];
    int     pid;
    int     print[2];

    if (pipe(output) == -1)
    {
        perror("piping");
        return (1);
    }
    pid = fork();
    if (pid == -1)
    {
        perror("Forking");
        close(output[1]);
        close(output[2]);
        return (1);
    }
    if (pid == 0)
    {
        if (input != NULL)
        {
            close(input[1]);
            dup2(input[0], 0);
            close(input[0]);
        }
        close(output[0]);
        if (cmds[1] != 0)
            dup2(output[1], 1);
        close(output[1]);
        /*if (input != NULL)
        {
            readed = read(0, buffer, 500);
            buffer[readed] = 0;
            write(1, buffer, strlen(buffer));
        }*/
        execve(cmds[0][0], cmds[0], NULL);
        exit(0);
    }
    else
    {
        if (input != NULL)
        {
            close(input[0]);
            close(input[1]);
        }
        if (cmds[1] != 0)
            pipe_loop(cmds + 1, i + 1, output);
        wait(NULL);
    }
}

int main(int argc, char **argv)
{
    char    *cmd[]={"/usr/bin/ls", NULL};
    char    *cmd1[]={"/usr/bin/grep", "fil", NULL};
    char    *cmd2[]={"/usr/bin/sleep", "2", NULL};
    char    *cmd3[]={"/usr/bin/cat", "-e", NULL};
    char    **cmds[5]={NULL, NULL, NULL, NULL, NULL};

    cmd1[1] = argv[1];
    cmds[0] = cmd2;
    cmds[1] = cmd;
    cmds[2] = cmd1;
    cmds[3] = cmd3;
    pipe_loop(cmds, 0, NULL);
    return (0);
}
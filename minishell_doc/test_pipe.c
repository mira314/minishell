#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

static void close_pipe(int *fds)
{
    close(fds[0]);
    close(fds[1]);
}

static void fork_fun(int *input, int *output, char ***cmds)
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
    execve(cmds[0][0], cmds[0], NULL);
    exit(5);
}

static int  on_forking_error_pipe(int *fds)
{
    perror("Forking");
    close_pipe(fds);
    return (1);
}   
int    pipe_loop(char ***cmds, int *input)
{
    int     output[2];
    int     pid;
    int     print[2];
    int     status;

    if (pipe(output) == -1)
    {
        perror("piping");
        return (1);
    }
    pid = fork();
    if (pid == -1)
        on_forking_error_pipe(output);   
    if (pid == 0)
        fork_fun(input, output, cmds);
    else
    {
        if (input != NULL)
            close_pipe(input);
        if (cmds[1] != 0)
        {
            pipe_loop(cmds + 1, output);
            wait(NULL);
        }
        else
        {
            wait(&status);
            if (WIFEXITED(status))
                printf("Exited with status %d\n", WEXITSTATUS(status));
            else if(WIFSIGNALED(status))
                printf("Terminated by signal %d\n", WTERMSIG(status));
            fflush(stdout);
        }
    }
}

int main(int argc, char **argv)
{
    char    *cmd0[]={"ping", NULL};
    char    **cmds[3]={NULL, NULL, NULL};

    cmds[0] = cmd0;
    pipe_loop(cmds, NULL);
    return (0);
}
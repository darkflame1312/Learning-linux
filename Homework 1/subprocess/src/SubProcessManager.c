#include "../inc/SubProcessManager.h"

void func()
{
    printf("wait signal");
    wait(0);
}

int pidprocess()
{
    printf("oke");
    int subproc = fork();
    if(subproc == 0)
    {
        printf("Child: %d\n", getpid());
    }
    else
    {
        signal(SIGCHLD, func);
        printf("parent: %d\n", getpid());
    }
    return 0;
}
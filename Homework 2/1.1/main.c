#include <signal.h>
#include <wait.h>
#include <unistd.h>
#include <sys/types.h>
#include </usr/include/x86_64-linux-gnu/bits/types/sigset_t.h>
#include </usr/include/x86_64-linux-gnu/bits/sigaction.h>
#include <stddef.h>
#include <stdio.h>

void func()
{
    printf("has signal");
    wait(0);
}

int main()
{
    //block SIGCHLD
    sigset_t newset, oldset;
    sigemptyset(&oldset);
    sigemptyset(&newset);
    sigprocmask(SIG_SETMASK, NULL, &oldset);
    sigaddset(&newset, SIGCHLD);
    sigprocmask(SIG_SETMASK, &newset, &oldset);
    
    int subproc = fork();
    if(subproc == 0)
    {
        printf("Child: %d\n", getpid());
    }
    else
    {
        signal(SIGCHLD, func);
        sleep(5);
        wait(0);
        printf("wait to unblock SIGCHLD");
        sigprocmask(SIG_SETMASK, &oldset, &newset);
        printf("unblock yeah!!!");
        printf("parent: %d\n", getpid());
        //while(1);
    }
    return 0;
}
// ket qua lenh SIGCHLD khi bi block se vao hang doi khi lenh va se gui khi dc unblock
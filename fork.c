#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
    if(fork()==0)
    {
        printf("child process\n");
        printf("%d-pid %d-ppid\n",getpid(),getppid());
    }
    else
    {
        wait(NULL);
        printf("parent process\n");
        printf("%d-pid %d-ppid\n",getpid(),getppid());
             
    }
    return 0;
}
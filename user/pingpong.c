#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define CHILDPID 0

int main()
{
    int fd[2];
    pipe(fd);
    int pid=fork();
    if(pid==CHILDPID)
    {       
        char buff;
        read(fd[0],&buff,1);
        printf("%d: received ping\n",getpid());
        write(fd[1],&buff,1);
        exit(0);
    }
    else
    {
        char buff='p';
        write(fd[1],&buff,1);
        read(fd[0],&buff,1);
        printf("%d: received pong\n",getpid());
        exit(0);
    }
}
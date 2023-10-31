#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define CHILDPID 0
#define NULL 0

void childprocess(int parentout)
{
    int prime;
    if(read(parentout,&prime,sizeof(prime))!=0)
    {
        printf("prime %d\n",prime);
        int fd[2];
        pipe(fd);
        int pid=fork();
        if(pid==CHILDPID)
        {
            close(fd[1]);
            childprocess(fd[0]);
        }
        else
        {
            close(fd[0]);
            int testnum;
            while(read(parentout,&testnum,sizeof(testnum))!=0)
            {
                if(testnum%prime!=0)
                {
                    write(fd[1],&testnum,sizeof(testnum));
                }
            }
            close(parentout);
            close(fd[1]);
            wait(NULL);
            exit(0);
        }
    }
    else
    {
        close(parentout);
        exit(0);
    }
}

void main()
{
    int fd[2];
    pipe(fd);
    int pid=fork();
    if(pid==CHILDPID)
    {
        close(fd[1]);
        childprocess(fd[0]);
    }
    else
    {
        close(fd[0]);
        for(int i=2;i<=35;i++)
        {
            write(fd[1],&i,sizeof(i));
        }
        close(fd[1]);
        wait(NULL);
        exit(0);
    }
}
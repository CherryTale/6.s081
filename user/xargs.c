#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define BUFSIZE 512
#define CHILDPID 0
#define NULL 0

void main(int argc,char* argv[])
{
    char buf[BUFSIZE];
    int n=0;
    while(read(0,&buf[n],1)==1)
    {
        n++;
        if(buf[n-1]=='\n')
        {
            buf[n-1]='\0';
            n=0;
            int pid=fork();
            if(pid==CHILDPID)
            {
                for(int i=0;i<argc;i++)
                {
                    argv[i]=argv[i+1];
                }
                argv[argc-1]=buf;
                exec(argv[0],argv);
            }
            else
            {
                wait(NULL);
            }
        }
    }
    exit(0);
}

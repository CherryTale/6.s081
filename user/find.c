#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char* fmtname(char *path)
{
    char *p;

    // Find first character after last slash.
    for(p=path+strlen(path); p >= path && *p != '/'; p--)
        ;
    p++;

    return p;
}

void find(char* path,char* name)
{
    struct stat st;
    stat(path, &st);

    switch(st.type)
    {
    case T_FILE:
        if(strcmp(fmtname(path),name)==0)
        {
            printf(path);
            printf("\n");
        }
        else
        {
            return;
        }
        break;

    case T_DIR:
        char buf[512], *p;
        strcpy(buf, path);
        p = buf+strlen(buf);
        *p++ = '/';
        int fd=open(path, 0);
        struct dirent de;
        while(read(fd, &de, sizeof(de)) == sizeof(de))
        {
            if(de.inum == 0)
                continue;
            if(strcmp(de.name,".")==0||strcmp(de.name,"..")==0)
                continue;
            memmove(p, de.name, DIRSIZ);
            p[DIRSIZ] = 0;
            find(buf,name);
        }
        close(fd);
        break;
    }
}

int main(int argc, char *argv[])
{
    if(argc!=3)
    {
        printf("error\n");
    }
    find(argv[1],argv[2]);
    exit(0);
}

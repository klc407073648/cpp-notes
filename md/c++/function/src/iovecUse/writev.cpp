#include<stdio.h>
#include<sys/uio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<string.h>

void sys_err(const char *ptr,int num)
{
    perror(ptr);
    exit(-1);
}

int main(int argc,char **argv)
{
    struct iovec iov[3];
    char *p1 = "I";
    char *p2 = " am";
    char *p3 = " happy.\n";
    iov[0].iov_base = p1;
    iov[0].iov_len = strlen(p1);

    iov[1].iov_base = p2;
    iov[1].iov_len = strlen(p2);

    iov[2].iov_base = p3;
    iov[2].iov_len = strlen(p3);
    ssize_t ret = writev(STDOUT_FILENO,iov,3);
    if(ret < 0)
    {
        sys_err("writev",-1);
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/uio.h>

#define BUF_SIZE 100

int main()
{
    char buf1[BUF_SIZE] = { 0 };
    char buf2[BUF_SIZE] = { 0 };
    char buf3[BUF_SIZE] = { 0 };
    struct iovec iov[3];
    ssize_t nread;

    iov[0].iov_base = buf1;
    iov[0].iov_len = 5;
    iov[1].iov_base = buf2;
    iov[1].iov_len = 8;
    iov[2].iov_base = buf3;
    iov[2].iov_len = BUF_SIZE;

    nread = readv(STDIN_FILENO, iov, 3);
    printf("%ld bytes read.\n", nread);
    printf("buf1: %s\n", buf1);
    printf("buf2: %s\n", buf2);
    printf("buf3: %s", buf3);
    
    return 0;
}

#include <stdio.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char buf1[5], buf2[10];
    struct iovec iov[2];
    iov[0].iov_base = buf1;
    iov[0].iov_len = 5;
    iov[1].iov_base = buf2;
    iov[1].iov_len = 10;

    int fd = open("a.txt", O_RDWR);
    if (fd < 0)
    {
        perror("open");
        return -1;
    }
    int rsize = readv(fd, iov, 2); // 从文件a.txt中读取数据，存到iov[2]中的buf1、buf2
    printf("rsize = %d\n", rsize);

    close(fd);

    fd = open("b.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd < 0)
    {
        perror("open");
        return -1;
    }

    int wsize = writev(fd, iov, 2); // 将iov[2]中的buf1、buf2，写入到文件b.txt
    printf("wsize = %d\n", wsize);

    close(fd);
    return 0;
}

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>

int main()
{
    // 在Linux中，socket对象是一个文件描述符
    // socket函数可以创建socket
    int fd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9988);
    addr.sin_addr.s_addr = 0;

    int ret = bind(fd, (struct sockaddr*)&addr, sizeof(addr));


    char buf[1024];
    memset(buf, 0, sizeof(buf));

    recv(fd, buf, sizeof(buf), 0);
    int len = *(int*)buf;
    char* filename = buf+4;

    int filefd = open(filename, O_WRONLY|O_CREAT, 0777);

    while(len > 0)
    {
        ret = recv(fd, buf, sizeof(buf), 0);
        write(filefd, buf, ret);
        len -= ret;
    }

    close(filefd);
    close(fd);


    printf("%s\n", buf);

}

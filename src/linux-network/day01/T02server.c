#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

int main()
{
    // 在Linux中，socket对象是一个文件描述符
    // socket函数可以创建socket
    int fd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9988); // 端口是16位的整数，0～65535
    addr.sin_addr.s_addr = 0;

    int ret = bind(fd, (struct sockaddr*)&addr, sizeof(addr));


    char buf[1024];
    recv(fd, buf, sizeof(buf), 0);

    printf("%s\n", buf);
    close(fd);
}

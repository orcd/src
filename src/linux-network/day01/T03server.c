#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

int main()
{
    // 在Linux中，socket对象是一个文件描述符
    // socket函数可以创建socket
    int fd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9988);
    addr.sin_addr.s_addr = 0;

    int opt = 1;
    setsockopt(fd, SOL_SOCKET, SO_RESUEADDR, (char*)&opt, sizeof(opt));

    int ret = bind(fd, (struct sockaddr*)&addr, sizeof(addr));

    char buf[1024];
    struct sockaddr addrfrom;
    while(1)
    {
        socklen_t len = sizeof(addrfrom);
        memset(buf, 0, sizeof(buf));
        recvfrom(fd, buf, sizeof(buf), 0, &addrfrom, &len);
        printf("%s", buf);

        // 获取用户输入
        fgets(buf, sizeof(buf), stdin);
        sendto(fd, buf, strlen(buf), 0, &addrfrom, len);
    }
}

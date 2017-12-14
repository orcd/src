#include "../header.h"
int main()
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    // 连接：跟UDP不同
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9999);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    getchar();
    connect(fd, (struct sockaddr*)&addr, sizeof(addr));

    send(fd, "hello", 5, 0);

    char buf[1024];
    memset(buf, 0, sizeof(buf));
    recv(fd, buf, sizeof(buf), 0);
    printf("%s\n", buf);

    close(fd);
}

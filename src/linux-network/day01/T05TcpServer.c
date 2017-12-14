#include "../header.h"
int main()
{
    int serverfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9999);
    addr.sin_addr.s_addr = INADDR_ANY; // INADDR_ANY == 0

    int ret = bind(serverfd, (struct sockaddr*)&addr, sizeof(addr));

    // 监听：跟UDP不同
    listen(serverfd, 10);

    printf("before accept\n");
    // 接收连接：跟UDP不同，阻塞调用
    int fd = accept(serverfd, NULL, NULL);
    printf("after accept\n");

    char buf[1024];
    memset(buf, 0, sizeof(buf));
    recv(fd, buf, sizeof(buf), 0);

    printf("%s\n", buf);

    send(fd, "server", 6, 0);

    close(fd);
    close(serverfd);
}

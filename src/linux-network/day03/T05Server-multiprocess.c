
#include "../header.h"

// 多进程服务器不能有全局变量
// 如果需要存储数据，应该把数据存储在第三台机器上

void handle_connect(sock)
{
    char buf[8192];
    int ret = read(sock, buf, sizeof(buf));
}

int main()
{
    int server = startTcpServer(9999, "0.0.0.0", 10);

    while(1)
    {
        int sock = accept(server, NULL, NULL);

        pid_t pid = fork();
        if(pid == 0)
        {
            close(server);
            handle_connect(sock);
            exit(1);
        }
        else
        {
            // parent
            close(sock);
        }
    }
}

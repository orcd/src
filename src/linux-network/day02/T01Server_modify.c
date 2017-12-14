
#include "../header.h"

// Server
int main()
{
    int server = startTcpServer(9999, "0.0.0.0", 50);

    int sock = accept(server, NULL, NULL);

    mkdir("recvdir", 0777);
    chdir("recvdir");


    // 读文件名长度
    int filenamelen; // 内存中保存的数据000000a0
    // 被解析成 a0000000
    doRead(sock, &filenamelen, 4); // 对方发送四个，这边一定接收四个么？
    filenamelen = ntohl(filenamelen);

    // 读文件名
    char buf[1024];
    memset(buf, 0, sizeof(buf));
    doRead(sock, buf, filenamelen);

    int filefd = open(buf, O_WRONLY|O_CREAT, 0666);
    // 读文件内容长度
    int filelen;
    int ret = doRead(sock, &filelen, 4);
    filelen = ntohl(filelen);
    while(1)
    {
        ret = read(sock, buf, sizeof(buf));
        if(ret > 0)
        {
            write(filefd, buf, ret);
            filelen -= ret;
            if(filelen == 0)
                break;
        }
        else
        {
            break;
        }
    }

    close(filefd);
    close(sock);
    close(server);

}

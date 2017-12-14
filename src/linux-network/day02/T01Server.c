
#include "../header.h"

// Server
int main()
{
    int server = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    // htons --> host to network short 
    // ntohs --> network to host short
    // htonl
    // ntohl
    // htonll
    addr.sin_port = htons(9999);
    addr.sin_addr.s_addr = 0;

    int ret = bind(server, (struct sockaddr*)&addr, sizeof(addr));
    if(ret < 0)
    {
        printf("bind error\n");
        return 0;
    }

    listen(server, 250);

    int sock = accept(server, NULL, NULL);


    // 读文件名长度
    int filenamelen;
    read(sock, &filenamelen, 4);

    // 读文件名
    char buf[1024];
    memset(buf, 0, sizeof(buf));
    read(sock, buf, filenamelen);

    int filefd = open(buf, O_WRONLY|O_CREAT, 0666);
    // 读文件内容长度
    int filelen;
    read(sock, &filelen, 4);
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

// Server
//

#include "../header.h"

int main()
{
    chdir("recvdir");

    int server = startTcpServer(9999, "0.0.0.0", 10);
    int sock = accept(server, NULL, NULL);

    char buf[1024];

    while(1)
    {
        char type;
        if(doRead(sock, &type, 1) == -1)
            break;

        printf("recv type %c\n", type);


        if(type == 'd')
        {
            int len;
            doRead(sock, &len, 4);
            len = ntohl(len);
            memset(buf, 0, sizeof(buf));
            doRead(sock, buf, len);
            mkdir(buf, 0777);
            chdir(buf);
            printf("recv dir %s\n", buf);
        }
        else if(type=='r') // 常规文件
        {
            int len;
            doRead(sock, &len, 4);
            len = ntohl(len);
            memset(buf, 0, sizeof(buf));
            doRead(sock, buf, len); // buf==文件名

            printf("recv file %s, filelen=%d\n", buf, len);

            // 读文件长度
            doRead(sock, &len, 4);
            len = ntohl(len);

            int filefd = open(buf, O_WRONLY|O_CREAT, 0666);
            int readlen = 0;
            while(readlen < len)
            {
                int remain = len - readlen;
                if (remain > sizeof(buf))
                    remain = sizeof(buf);

                int ret = read(sock, buf, remain);
                printf("recv filecontent from socket, ret is %d\n", ret);
                if(ret > 0)
                {
                    readlen += ret;
                    write(filefd, buf, ret);
                }
                else
                {
                    return 0;
                }
            }
            close(filefd);

        }
        else if(type=='u')
        {
            chdir("..");
        }
        else if(type == 'o')
        {
            break;
        }
    }
}

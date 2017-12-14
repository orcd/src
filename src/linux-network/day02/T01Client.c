#include "../header.h"

// Client   
// ./T01Client aaa.txt
int main(int argc, char* argv[])
{
    const char* filename = argv[1];
    char dfilename[1024];
    sprintf(dfilename, "%s_dest", filename);

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9999);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");


    int ret = connect(sock, (struct sockaddr*)&addr, sizeof(addr));


    // 规矩：协议
    //
    // 发送文件名的长度
    int filenamelen = strlen(dfilename);
    // 发送四个字节的整数
    send(sock, &filenamelen, 4, 0);
    send(sock, dfilename, filenamelen, 0);

    struct stat stat_buf;
    stat(filename, &stat_buf);
    int filelen = stat_buf.st_size;

    send(sock, &filelen, 4, 0);

    int filefd = open(filename, O_RDONLY);

    char buf[1024];
    while(1)
    {
        ret = read(filefd, buf, sizeof(buf));
        if(ret > 0)
        {
            send(sock, buf, ret, 0);
        }
        else
        {
            break;
        }
    }

    close(filefd);
    close(sock);
}

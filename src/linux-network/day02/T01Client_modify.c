#include "../header.h"

// Client   
// ./T01Client aaa.txt
// ./T01Client aaa/bbb.txt
// ./T01Client ./aaa/bbb.txt
// ./T01Client ../../aaa/bbb.txt
// ./T01Client /home/xueguoliang/aaa.txt
int main(int argc, char* argv[])
{
    // 目录/文件
    const char* filename = argv[1];
    char* dir;
    char* file;
    getPathAndFile(filename, &dir, &file);

    chdir(dir);

    int sock = connectServer(9999, "127.0.0.1");

    // 规矩：协议
    //
    // 发送文件名的长度
    int filenamelen = strlen(file);
    int tmp = htonl(filenamelen);

    // 发送四个字节的整数
    doWrite(sock, &tmp, 4);
    // 发送文件名
    doWrite(sock, file, filenamelen);

    int filelen = getFilelen(filename);
    tmp = htonl(filelen);

    doWrite(sock, &tmp, 4);

    int filefd = open(file, O_RDONLY);

    char buf[1024];
    while(1)
    {
        int ret = read(filefd, buf, sizeof(buf));
        if(ret > 0)
        {
            doWrite(sock, buf, ret);
        }
        else
        {
            break;
        }
    }

    close(filefd);
    close(sock);
}

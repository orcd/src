#include <sys/types.h>          /* See NOTES */
#include <string.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    int fd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9988);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");


    const char* filename = argv[1];
    char buf[1024];

    struct stat statbuf;
    int ret = lstat(filename, &statbuf);
    if(ret != 0)
    {
        printf("file not exist %s\n", filename);
        return 0;
    }

    // buf的前面四个字节等于文件长度
    *(int*)buf = statbuf.st_size;

    strcpy(buf+4, filename);
    strcat(buf+4, "1");

    // 发送这个buf
    sendto(fd, buf, strlen(filename) + 5, 0, (struct sockaddr*)&addr, sizeof(addr));

    int filefd = open(filename, O_RDONLY);
    while(1)
    {
        int ret = read(filefd, buf, sizeof(buf));
        if(ret == 0)
            break;
        sendto(fd, buf, ret, 0, (struct sockaddr*)&addr, sizeof(addr));
    }

    close(filefd);
    close(fd);
}

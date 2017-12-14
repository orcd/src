#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>

int main()
{
    int fd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9988);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    while(1)
    {
        char buf[1024];
        fgets(buf, sizeof(buf), stdin);

        sendto(fd, buf, strlen(buf), 0, (struct sockaddr*)&addr, sizeof(addr));

        memset(buf, 0, sizeof(buf));
        recv(fd, buf, sizeof(buf), 0);
        printf("%s", buf);
    }

}

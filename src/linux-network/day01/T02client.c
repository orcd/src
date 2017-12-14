#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>

int main()
{
    int fd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9988);
    addr.sin_addr.s_addr = inet_addr("255.255.255.255");

    // 设置这个socket，让他有能力发送广播
    int opt = 1; // True  
    setsockopt(fd, SOL_SOCKET, SO_BROADCAST, (char*)&opt, sizeof(opt)); 
    
    sendto(fd, "hello", 6, 0, (struct sockaddr*)&addr, sizeof(addr));

    close(fd);
}

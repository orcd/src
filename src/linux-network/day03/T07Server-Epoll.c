#include "../header.h"

int read_data(int sock)
{
    char buf[1024];
    memset(buf, 0, sizeof(buf));
    int ret = read(sock, buf, sizeof(buf));
    if(ret > 0)
    {
        printf("%s\n", buf);
        return 0;
    }
    return -1;
}


int main()
{
    int server = startTcpServer(9999, "0.0.0.0", 10);
    set_nonblock(server);

    int epollfd = epoll_create(1024);
    addEpoll(epollfd, server, EPOLLIN);

    struct epoll_event ev[8];
    while(1)
    {
        int count = epoll_wait(epollfd, ev, 8, 5000);
        if(count < 0)
        {
            printf("epoll error %d\n", errno);
            return 0;
        }

        if(count == 0)
            continue;

        // ret > 0
        int i;
        for(i=0; i<count; ++i)
        {
            if(ev[i].data.fd == server)
            {
                while(1)
                {
                    int sock = accept(server, NULL, NULL);
                    if(sock == -1)
                        break;
                    addEpoll(epollfd, sock, EPOLLIN);
                }
            }
            else
            {
                int ret = read_data(ev[i].data.fd);
                if(ret < 0)
                {
                    // close会自动将socket从epoll集合中取出
                    close(ev[i].data.fd);
                }       
            }
        }
    }
}


#include "../header.h"
        
int maxfd;
fd_set set_back;

int main()
{
    int server = startTcpServer(9999, "0.0.0.0", 10);
    maxfd = server;
    FD_ZERO(&set_back);
    FD_SET(server, &set_back);

    while(1)
    {
        fd_set set;
        memcpy(&set, &set_back, sizeof(set));
        // set = set_back;

        struct timeval tv;
        tv.tv_sec = 5;
        tv.tv_usec = 0;

        int ret = select(maxfd + 1, &set, NULL, NULL, &tv);
        if(ret > 0)
        {
            int fd;
            int m = maxfd;
            for(fd=0; fd<=m; ++fd)
            {
                if(FD_ISSET(fd, &set))
                {
                    if(fd == server)
                    {
                        int sock = accept(server, NULL, NULL);
                        FD_SET(sock, &set_back);
                        if(sock > maxfd) maxfd = sock;
                    }
                    else
                    {
                        char buf[8192];
                        memset(buf, 0, sizeof(buf));
                        int ret = read(fd, buf, sizeof(buf));
                        if(ret > 0)
                            printf("%s\n", buf);
                        else // ret <= 0
                        {
                            FD_CLR(fd, &set_back);
                            if(fd == maxfd) maxfd --;
                        }
                    }
                }
            }
        }

    }
}


#include <signal.h>
#include <errno.h>
#include <pthread.h>
#include <sys/types.h>          /* See NOTES */
#include <string.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/epoll.h>

// 一定读完整的len字节数，然后再返回
static inline int doRead(int sock, void* buf, int len)
{
    int already_read = 0;
    while(already_read != len)
    {
        int ret = read(sock, buf + already_read, len - already_read);
        if(ret > 0)
            already_read += ret;
        else
            return -1;
    }

    return 0;
}

static inline int doWrite(int sock, const void*  buf, int len)
{
    int already_write = 0;
    while(already_write != len)
    {
        int ret = write(sock, buf + already_write, len - already_write);
        if (ret > 0)
            already_write += ret;
        else
            return -1;
    }
    return 0;
}

static inline int startTcpServer(unsigned short port, const char* ip, int backlog)
{
    int server = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);
    int ret = bind(server, (struct sockaddr*)&addr, sizeof(addr));
    if(ret < 0)
    {
        box_log("bind error");
        exit(1);
    }

    listen(server, backlog);
    return server;
}

static inline int connectServer(unsigned short port, const char* ip)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    int ret = connect(sock, (struct sockaddr*)&addr, sizeof(addr));
    if(ret == 0)
        return sock;

    close(sock);
    return -1;
}

static inline int getFilelen(const char* filename)
{
    struct stat buf;
    int ret = stat(filename, &buf);
    if(ret < 0)
    {
        return -1;
    }

    return buf.st_size;
}


static inline void getPathAndFile(const char* filepath, char** dir, char** file)
{
    static char fullpath [1024];
    realpath(filepath, fullpath);
    char* pos = rindex(fullpath, '/');
    *dir = fullpath;
    *file = pos+1;
    *pos = 0;
}


static inline void set_nonblock(int fd)
{
    int flag = fcntl(fd, F_GETFL);
    flag |= O_NONBLOCK;
    fcntl(fd, F_SETFL, flag);
}

static inline void addEpoll(int epollfd, int sock, int events)
{
    struct epoll_event ev;
    ev.data.fd = sock;
    ev.events = events;

    if(epoll_ctl(epollfd, EPOLL_CTL_ADD, sock, &ev) < 0)
    {
        epoll_ctl(epollfd, EPOLL_CTL_MOD, sock, &ev);
    }
}







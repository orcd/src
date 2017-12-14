

#include "../header.h"
#include "T06Server-Select-Chat.h"

int read_data(int sock)
{
#if 0
    char buflen[5];
    if(doRead(sock, buflen, 4) < 0)
    {
        // 这个socket有问题，删掉用户
        // 并且返回-1，让网络通信层次，做清理工作
        delUser(sock);
        return -1;
    }
    buflen[4] = 0;
    int len = atoi(buflen);

    char buf[8192];
    doRead(sock, buf, len);
    buf[len] = 0;
#endif

    // 把阻塞的socket改成非阻塞的socket
    // 提高效率，提高服务器容错性

    User* user = findUserBySock(sock);
    // 接受报文的头，也就是报文的长度
    if(user->already_read_len < 4)
    {
        // 数据有多长不知道
        // 但是数据头部有多长是知道的
        int ret = read(sock, 
                user->buf + user->already_read_len, 
                4 - user->already_read_len);
        if(ret > 0)
        {
            // 记录已经收到的数据
            user->already_read_len += ret;
            if(user->already_read_len == 4)
            {
                user->buf[4] = 0;
                user->packet_len = atoi(user->buf);
            }
            return 0;
        }
        else if(ret == 0) // 对方关闭了socket
        {
            delUser(sock);
            return -1; // 让我方也关闭socket
        }
        else // ret < 0
        {
            // 一种是因为缓冲区没有数据，所以返回-1
            // 一种是因为socket出了问题，所以返回-1
            if(errno == EAGAIN)
            {
                return 0;
            }
            delUser(sock);
            return -1;
        }
    }
    else // already_read_len >= 4
    {
        int ret = read(sock, 
                user->buf + user->already_read_len, 
                user->packet_len - (user->already_read_len - 4));
        if(ret > 0)
        {
            user->already_read_len += ret;
            if(user->already_read_len == user->packet_len + 4)
            {
                user->buf[user->already_read_len] = 0;
                user->already_read_len = 0; // 准备下一次的接收                
            }
            else
            {
                return 0; // 等待下一次再次接收数据
            }
        }
        else if(ret == 0)
        {
            delUser(sock);
            return -1;
        }
        else // ret < 0 
        {
           if(errno == EAGAIN)
                return 0;
            delUser(sock);
            return -1; 
        }
    }

    char* buf = user->buf+4;

    // 对报文进行初级处理
    // 所谓初级处理：解包
    char* cmd = strtok(buf, "|");
    if(strcmp(cmd, "name") == 0)
    {
        char* name = strtok(NULL, "\0");
        set_name(sock, name);
    }
    else if(strcmp(cmd, "msg") == 0)
    {
        char* toname = strtok(NULL, "|");
        char* content = strtok(NULL, "\0");
        send_msg(sock, toname, content);
    }
}

int main()
{
    // 记录select时候的最大文件描述符
    // 如果有新的socket连接，或者有socket断开时，会改变这个值
    int maxfd;
    // 记录目前我们的程序中，有多少活跃的socket
    fd_set set_back;

    // 创建一个服务器socket，用于监听
    int server = startTcpServer(9999, "0.0.0.0", 10);

    set_nonblock(server);

    // 因为这个程序有新的socket
    // 所以要改变maxfd和set_back
    maxfd = server;
    FD_ZERO(&set_back);
    FD_SET(server, &set_back);

    // 进入select循环
    while(1)
    {
        // 要监听所有服务器，但是因为select会修改集合
        // 所以把set_back拷贝一份
        fd_set set;
        memcpy(&set, &set_back, sizeof(set));
        // set = set_back;

        struct timeval tv;
        tv.tv_sec = 5;
        tv.tv_usec = 0;

        // 监听所有的socket
        int ret = select(maxfd + 1, &set, NULL, NULL, &tv);
        if(ret > 0)
        {
            int fd;
            int m = maxfd;
            for(fd=0; fd<=m; ++fd)
            {
                // 遍历所有的文件描述符
                if(FD_ISSET(fd, &set))
                {
                    // 是否是服务器
                    if(fd == server)
                    {
                        while(1)
                        {
                            // 调用accept接收连接
                            int sock = accept(server, NULL, NULL);
                            if(sock == -1)
                                break;

                            set_nonblock(sock);

                            // 对于新的socket，要更改set_back和maxfd
                            FD_SET(sock, &set_back);
                            if(sock > maxfd) maxfd = sock;

                            // 调用业务模块的函数，增加用户
                            new_user(sock);
                        }
                    }
                    else
                    {
                        // 读取和处理数据，
                        // 如果返回值不是0
                        // 那么要把socket清理掉
                        if(read_data(fd) != 0)
                        {
                            FD_CLR(fd, &set_back);
                            if(fd == maxfd) maxfd --;
                            close(fd);
                        }
                    }
                }
            }
        }
    }
}

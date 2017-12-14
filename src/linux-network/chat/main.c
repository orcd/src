#include <box/box.h>
#include "global.h"

void handle_tcp_socket(int sock)
{
    // 接收文件
    char type;
    doRead(sock, &type, 1);

    box_log("开始接收文件....\n");
    int filenamelen;
    doRead(sock, &filenamelen, 4);
    filenamelen = ntohl(filenamelen);
    box_log("filename len=%d\n", filenamelen);

    char buf[1024];
    doRead(sock, buf, filenamelen);
    buf[filenamelen] = 0;
    FILE* fp = fopen(buf, "w");
    box_log("filename = %s, fp=%p\n", buf, fp);

    int filelen;
    doRead(sock, &filelen, 4);
    filelen = ntohl(filelen);
    box_log("filelen=%d\n", filelen);

    while(1)
    {
        int ret = read(sock, buf, sizeof(buf));
        if(ret <= 0)
            break;
        fwrite(buf, ret, 1, fp);
    }

    fclose(fp);
    box_log("接收文件结束\n");

    if(type=='d')
    {
        // 解压...
    }
    // recv;
    exit(0);

}

void accept_tcp(box_channel* c)
{
    while(1)
    {
        int tcp_socket = accept(c->sock, NULL, NULL);
        if(tcp_socket < 0)
        {
            box_log("no socket connect .... break\n");
            break;
        }

        pid_t pid = fork();
        if(pid == 0)
        {
            box_log("new socket accepted tcp_socket= %d\n", tcp_socket);
            handle_tcp_socket(tcp_socket);
            exit(0);
        }
#if 0
        box_log("new socket accepted tcp_socket= %d\n", tcp_socket);
        box_channel* c1 = box_channel_create(tcp_socket, read_tcp);
        box_add(c1);
#endif
    }
}

void read_stdin(box_channel* c);
void read_udp(box_channel* c);

int udp_socket;

void sighandle(int v)
{
    if(v == SIGCHLD)
    {
        while(1)
        {
            int  ret = waitpid(-1, NULL,WNOHANG);
            if(ret <= 0) break;
        }
    }
}

int main()
{
    signal(SIGCHLD, sighandle);
    box_init();

    // 把文件描述符，加入到box
    box_channel* c = box_channel_create(0, read_stdin);
    box_add(c);

    // 创建一个UDP socket
    udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(UDP_PORT);
    addr.sin_addr.s_addr = 0;
    int ret = bind(udp_socket, (struct sockaddr*)&addr, sizeof(addr));
    int opt = 1;
    setsockopt(udp_socket, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(opt));

    if(ret < 0)
    {
        box_log("udp bind error\n");
        exit(1);
    }
    c = box_channel_create(udp_socket, read_udp);
    box_add(c);

    // 创建一个TCP Server
    int tcp_server = __box_start_server(TCP_PORT, "0.0.0.0", 10);
    box_set_nonblock(tcp_server);
    c = box_channel_create(tcp_server, accept_tcp);
    box_add(c);



    box_run();
    box_fini();
}

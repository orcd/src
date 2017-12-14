
#include <event2/event.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/bufferevent_struct.h>
#include <event2/buffer.h>
#include "T03ChatServer.h"

void eventcb(struct bufferevent *bev, short what, void *ctx);
void readcb_packet(struct bufferevent* bev, void* ctx);
void readcb_header(struct bufferevent *bev, void *ctx);

void readcb_packet(struct bufferevent* bev, void* ctx)
{
    int len = (intptr_t)ctx;
    char buf[8192];
    bufferevent_read(bev, buf, len);
    buf[len] = 0;
    handlePacket(bev, buf);

    printf("read buffer is %s, len=%d\n", buf, len);

    struct evbuffer* rbuf = bufferevent_get_input(bev);
    int bufferlen = evbuffer_get_length(rbuf);
    // 准备收下一个报文
    if(bufferlen >= 4)
    {
          readcb_header(bev, NULL);
    }
    else
    {
        bufferevent_setwatermark(bev, EV_READ, 4, 8192);
        bufferevent_setcb(bev, readcb_header, NULL, eventcb, NULL);
    }
}

void readcb_header(struct bufferevent *bev, void *ctx)
{
    char buf[5];
    buf[0] = 0;
    bufferevent_read(bev, buf, 4);

    int len = atoi(buf); // 9999
    printf("read heaer %d\n", len);

    // 检查一下，缓冲区的长度是不是超过了len，如果超过了len
    // 那就不用等，直接read_packet处理就好了
    struct evbuffer* rbuf = bufferevent_get_input(bev);
    int bufferlen = evbuffer_get_length(rbuf);
    if(bufferlen >= len)
    {
          readcb_packet(bev, (void*)(intptr_t)len);
    }
    else
    {
        bufferevent_setwatermark(bev, EV_READ, len, 8192);
        bufferevent_setcb(bev, readcb_packet, NULL, eventcb, (void*)(intptr_t)len);
    }
}

void eventcb(struct bufferevent *bev, short what, void *ctx)
{
    if((what & BEV_EVENT_EOF)  > 0)
    {
        printf("delete event\n");
        bufferevent_free(bev);
        delUser(bev);
    }
}

void listen_cb(struct evconnlistener * listener,
               evutil_socket_t sock,
               struct sockaddr * addr,
               int socklen, void *ptr)
{
    struct event_base* base = (struct event_base*)ptr;

    // 使用新的sock去创建一个event，再把event加入到集合中
    struct bufferevent* bev = bufferevent_socket_new(
                base, sock, BEV_OPT_CLOSE_ON_FREE); // 已初始化

    // 设置回调函数
    bufferevent_setcb(bev,  readcb_header,  NULL, eventcb, ptr);

    // 设置水位
    bufferevent_setwatermark(bev, EV_READ, 4, 8192);

    // 把bev设置成未决状态
    bufferevent_enable(bev, EV_READ); // 状态是否永久的？？？不是

    addUser(bev);
}

int main()
{
    // 创建一个event_base
    struct event_base* base = event_base_new();

    struct sockaddr_in addr;
    addr.sin_port = htons(9999);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;

    // 创建listener，startTcpServer
    // listener是一个event，evconnlistener_new_bind创建了一个event
    // 处于已初始化状态

    struct evconnlistener* listener =
        evconnlistener_new_bind(
                base,   // 这个listener放到哪个集合中
                listen_cb, // listen回调函数
                base, // 回调函数参数
                LEV_OPT_CLOSE_ON_FREE|LEV_OPT_REUSEABLE, // 监听选项
                250,// listen(server, backlog)
                (struct sockaddr*)&addr, // bind地址
                sizeof(addr));

    // 让lisntener进入未决状态
    // listener的事件是持久的
    evconnlistener_enable(listener);

    // 消息循环
    /*
     * while(1)
     * {
     *
     * }
    */
    event_base_dispatch(base);

    // 不用时，free这个event_base
    event_base_free(base);
}

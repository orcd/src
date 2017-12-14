
#include "../header.h"
#include <event2/event.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/bufferevent_struct.h>

void readcb(struct bufferevent *bev, void *ctx)
{
    // read data from bufferevent...
    char buf[1024];
    // 从bufferevent中抽取数据
    int ret = bufferevent_read(bev, buf, sizeof(buf));
    if(ret < 0)
    {
        // error
        printf("error");
    }

    printf("%s\n", buf);

    bufferevent_write(bev, "world", 5);


}

void eventcb(struct bufferevent *bev, short what, void *ctx)
{
    if((what & BEV_EVENT_EOF)  > 0)
    {
        printf("delete event\n");
        bufferevent_free(bev);
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
    bufferevent_setcb(bev,  readcb,  NULL, eventcb, ptr);

    // 把bev设置成未决状态
    bufferevent_enable(bev, EV_READ); // 状态是否永久的？？？不是

    printf("%x\n", bev->enabled);
}

int main()
{
    // 创建一个event_base
    struct event_base* base = event_base_new();

    struct sockaddr_in addr;
    addr.sin_port = htons(9988);
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


#include "../header.h"

// libevent的头文件 /usr/local/include
#include <event2/event.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>

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

}

void eventcb(struct bufferevent *bev, short what, void *ctx)
{
    if((what & BEV_EVENT_EOF)  > 0)
    {
        printf("delete event\n");
        bufferevent_free(bev);
    }
}

// 客户端连接的回调函数
void listen_cb(struct evconnlistener *listener, 
        evutil_socket_t newfd,  // int newfd = accept(server, NULLL, NULL);
        struct sockaddr *addr,  // 对方ip地址
        int socklen, 
        void *ptr)
{
    struct event_base* evbase = evconnlistener_get_base(listener);

    /* add newfd to evbase */
    struct bufferevent* bev = bufferevent_socket_new(evbase, newfd, BEV_OPT_CLOSE_ON_FREE);

    /* setup read and event callback function */
    bufferevent_setcb(bev, readcb, NULL, eventcb, NULL);

    bufferevent_enable(bev, EV_READ);
}

int main()
{
    // 相当于epoll对象
    struct event_base* evbase = event_base_new();   

    struct sockaddr_in addr;
    addr.sin_port = htons(9988);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY; 

    // 创建listener，startTcpServer
    struct evconnlistener* listener =
        evconnlistener_new_bind(
                evbase,   // 这个listener放到哪个集合中
                listen_cb, // listen回调函数
                NULL, // 回调函数参数
                LEV_OPT_CLOSE_ON_FREE|LEV_OPT_REUSEABLE, // 监听选项
                250,// listen(server, backlog)
                (struct sockaddr*)&addr, // bind地址
                sizeof(addr));

    // 启动监听
    evconnlistener_enable(listener);

    /*
     *  while(1)
     *  {
     *      epoll_wait(...);
     *  }
     * */
    event_base_dispatch(evbase);

    event_base_free(evbase);

    return 0;
}

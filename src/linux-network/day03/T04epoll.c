#include "../header.h"
int main()
{
    int mice = open("/dev/input/mice", O_RDONLY);
    int key = open("/dev/input/event1", O_RDONLY);

    // 创建了一个epoll对象，epoll对象也是一个文件描述符
    // 也可以看成是一个文件描述符的集合
    int epollfd = epoll_create(1024);

    // 把mice和key 加入到 epoll集合中
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = mice;

    // epoll_ctl
    epoll_ctl(epollfd, EPOLL_CTL_ADD, mice, &ev);

    ev.data.fd = key;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, key, &ev);

    while(1)
    {
        struct epoll_event evout[8];
        int ret = epoll_wait(epollfd, evout, 8, 5000);
        if(ret < 0)
        {
            return 0;
        }

        if(ret > 0)
        {
            int i;
            for(i=0; i<ret; ++i)
            {
                if(evout[i].data.fd == mice)
                {
                    // 鼠标有消息
                    char buf[1024];
                    read(mice, buf, sizeof(buf));
                    printf("mice move\n");

                }
                else if(evout[i].data.fd == key)
                {
                    // 键盘有消息
                    char buf[1024];
                    read(key, buf, sizeof(buf));
                    printf("key press\n");
                }
            }
        }
    }
}

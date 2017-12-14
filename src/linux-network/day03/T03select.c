#include "../header.h"

int main()
{
    int mice = open("/dev/input/mice", O_RDONLY);
    int key = open("/dev/input/event1", O_RDONLY);

    while(1)
    {
        int maxfd = mice > key ? mice : key;
        fd_set set;
        FD_ZERO(&set); // set中没有任何的文件描述符
        FD_SET(mice, &set);
        FD_SET(key, &set);


        struct timeval tv;
        tv.tv_sec = 5; // 秒
        tv.tv_usec = 0; // 微秒为单位 1/1000000

        int ret = select(maxfd+1, &set, NULL, NULL, &tv);
        printf("select over ret=%d\n", ret);

        if(ret < 0)
        {
            return 0;
        }

        char buf[1024];
        if(FD_ISSET(mice, &set))
        {
            int ret = read(mice, buf, sizeof(buf));
            printf("mice move\n");
        }
        if(FD_ISSET(key, &set))
        {
            int ret = read(key, buf, sizeof(buf));
            printf("key press\n");
        }
    }
}

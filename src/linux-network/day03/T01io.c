#include "../header.h"

int main()
{
    int mice = open("/dev/input/mice", O_RDONLY|O_NONBLOCK);
    int key = open("/dev/input/event1", O_RDONLY|O_NONBLOCK);

    while(1)
    {
        usleep(100*1000);

        char buf[1024];
        int ret = read(mice, buf, sizeof(buf));
        if(ret > 0)
            printf("mice move, ret=%d\n", ret);

        ret = read(key, buf, sizeof(buf));
        if(ret > 0)
            printf("key press, ret=%d\n", ret);
    }
}



#include "../header.h"
int main()
{
    int fd = connectServer(9998, "127.0.0.1");
    write(fd, "hello", 5);
}


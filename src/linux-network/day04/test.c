

#include "../header.h"
int main()
{
    int fd = connectServer(9988, "127.0.0.1");
    write(fd, "hel", 3);
    write(fd, "world", 5);

    char buf[1024];
    read(fd, buf, sizeof(buf));
    printf("%s\n", buf);
}

int main1()
{
    int i;
    for(i=0; i<1; ++i)
    {
        pid_t pid = fork();
        if(pid == 0)
        {
            main1();
            exit(1);
        }
    }
}

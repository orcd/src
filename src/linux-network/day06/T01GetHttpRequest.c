
#include "../header.h"

int main()
{
    int server = startTcpServer(8889, "0.0.0.0", 10);

    int sock = accept(server, NULL, NULL);

    char buf[8192];
    memset(buf, 0, sizeof(buf));

    int ret = read(sock, buf, sizeof(buf));
    if(ret > 0)
    {
        printf("%s\n", buf);
    }
}

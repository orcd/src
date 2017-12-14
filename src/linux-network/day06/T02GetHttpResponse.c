
#include "../header.h"

char* buf = "GET /a.html HTTP/1.1\r\n"
"Host: 127.0.0.1:80\r\n"
"User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:55.0) Gecko/20100101 Firefox/55.0\r\n"
"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
"Accept-Language: zh-CN,zh;q=0.8,en-US;q=0.5,en;q=0.3\r\n"
"Accept-Encoding: gzip, deflate\r\n"
"Connection: keep-alive\r\n"
"Upgrade-Insecure-Requests: 1\r\n"
"\r\n";



int main()
{
    int sock = connectServer(80, "127.0.0.1");

    write(sock, buf, strlen(buf));

    char resp[8192];

    read(sock, resp, sizeof(resp));

    printf("%s\n", resp);
}

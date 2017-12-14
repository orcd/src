// Client
#include "../header.h"

// type=='d' type=='r'
void sendfilename(int sock, char* filename, char type)
{
    doWrite(sock, &type, 1);
    int len = strlen(filename);
    int tmp = htonl(len);
    doWrite(sock, &tmp, 4);
    doWrite(sock, filename, len);

    printf("send filename=%s, type=%c\n", filename, type);
}

void sendfile(int sock, char* filename)
{
    sendfilename(sock, filename, 'r');

    int len = getFilelen(filename);
    len = htonl(len);
    doWrite(sock, &len, 4);

    int filefd = open(filename, O_RDONLY);
    int sendlen = 0;

    while(1)
    {
        char buf[1024];
        int ret = read(filefd, buf, sizeof(buf));
        printf("ret %d\n", ret);
        if(ret > 0)
        {
            doWrite(sock, buf, ret);
            sendlen += ret;
        }
        else
            break;
    }

    printf("send file content %d, filelen=%d\n", sendlen, ntohl(len));
    close(filefd);
}

// dirname = aaa 
// aaa(bbb, ccc, ddd 目录)
void senddir(int sock, char* dirname)
{
    sendfilename(sock, dirname, 'd');

    chdir(dirname);
    DIR* dir = opendir(".");
    struct dirent* entry;
    while(1)
    {
        entry = readdir(dir);
        if(entry == NULL) break;

        char* filename = entry->d_name;
        if(strcmp(filename, ".") == 0
                || strcmp(filename, "..") == 0)
            continue;

        if(entry->d_type == DT_DIR)
            senddir(sock, filename);
        else
            sendfile(sock, filename);
    }

    closedir(dir);
    chdir("..");
    char type='u';
    doWrite(sock, &type, 1);
}

int main(int argc, char* argv[])
{
    char* dirpath = argv[1];

    char* dir;
    char* dirname;
    getPathAndFile(dirpath, &dir, &dirname);

    chdir(dir);

    int sock = connectServer(9999, "127.0.0.1");

    senddir(sock, dirname);

    char type='o';
    doWrite(sock, &type, 1);

    close(sock);
}


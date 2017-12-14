
#include "../header.h"

int sock;

void* thread_func(void* ptr)
{
    char buf[8192];
    while(1)
    {
        buf[4] = 0;
        int ret = doRead(sock, buf, 4);
        if(ret < 0)
            exit(1);
        int len = atoi(buf);

        buf[len] = 0;
        doRead(sock, buf, len);

        // ack|info
        // msg|fromUser|msgcontent

        char* saveptr = NULL;
        char* cmd = strtok_r(buf, "|", &saveptr);
        if(strcmp(cmd, "ack") == 0)
        {
            char* info = strtok_r(NULL, "\0", &saveptr);
            printf("%s\n", info);
        }

        else if(strcmp(cmd, "msg") == 0)
        {
            char* fromUser = strtok_r(NULL, "|", &saveptr);
            char* msg = strtok_r(NULL, "\0", &saveptr);
            printf("%s说: %s\n", fromUser, msg);
        }
    }
}

int main()
{
    sock = connectServer(9999, "127.0.0.1");
    pthread_t tid;
    pthread_create(&tid, NULL, thread_func, NULL);

    while(1)
    {
        char buf[8192];
        fgets(buf, sizeof(buf), stdin);

        buf[strlen(buf)-1] = 0; // 去掉最后的\n

        // name|xxxx
        // msg|xiaowang|hello
        //
        
        char* saveptr = NULL;
        char* cmd = strtok_r(buf, "|", &saveptr);
        if(strcmp(cmd, "name") == 0)
        {
            char* name = strtok_r(NULL, "\0", &saveptr);
            if(strlen(name) == 0)
            {
                printf("name is null\n");
                continue;
            }

            char sendBuf[8192];
            sprintf(sendBuf, "%s|%s", cmd, name);

            int len = strlen(sendBuf);
            char buflen[5];
            sprintf(buflen, "%04d", len);

            doWrite(sock, buflen, 4);
            doWrite(sock, sendBuf, len);

        }
        else if(strcmp(cmd, "msg") == 0)
        {
            char* toName = strtok_r(NULL, "|", &saveptr);
            if(strlen(toName) == 0)
            {
                printf("toName is NULL\n");
                continue;
            }

            char* msgcontent = strtok_r(NULL, "\0", &saveptr);
            if(strlen(msgcontent) == 0)
            {
                printf("msg is NULL\n");
                continue;
            }

            char sendBuf[8192];
            sprintf(sendBuf, "%s|%s|%s", cmd, toName, msgcontent);

            int len = strlen(sendBuf);
            char buflen[5];
            sprintf(buflen, "%04d", len);

            doWrite(sock, buflen, 4);
            doWrite(sock, sendBuf, len);
        }
    }
}

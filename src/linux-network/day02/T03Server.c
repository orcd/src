
#include "../header.h"

// 有一个全局变量，把所有的用户保存起来
typedef struct User
{
    struct User* next;
    char name[32];
    int sock;
} User;

pthread_mutex_t mutex;
#define Lock(__mutex) pthread_mutex_lock(&__mutex)
#define Unlock(__mutex) pthread_mutex_unlock(&__mutex)

User* users = NULL;

User* addUser(int sock)
{
    User* user = malloc(sizeof(User));
    user->sock = sock;
    user->name[0] = 0; // 名字暂时是空的

    // 头插
    user->next = users;
    users = user;
    return user;
}

User* findUser(const char* name)
{
    User* user = users;

    while(user)
    {
        if(strcmp(user->name, name) == 0)
            break;
        user = user->next;
    }

    return user;
}

void delUser(User* user)
{
    User* node = users;
    if(node == user)
    {
        users = users->next;
        return;
    }

    while(node->next != user && node->next != NULL)
    {
        node = node->next;
    }

    if(node->next)
        node->next = node->next->next;
}


void transMsg(User* toUser, const char* msg, const char* fromUser)
{
    // 9999msg|fromUser|msg..
    char buf[8192];
    sprintf(buf, "msg|%s|%s", fromUser, msg);

    int len = strlen(buf);
    char buflen[5];
    sprintf(buflen, "%04d", len);

    // "9999msg|xiaoli|hello"
    doWrite(toUser->sock, buflen, 4);
    doWrite(toUser->sock, buf, len);
}

void ack(User* user, const char* info)
{
    // 9999msg|fromUser|msg..
    char buf[8192];
    sprintf(buf, "ack|%s", info);

    int len = strlen(buf);
    char buflen[5];
    sprintf(buflen, "%04d", len);

    // "9999msg|xiaoli|hello"
    doWrite(user->sock, buflen, 4);
    doWrite(user->sock, buf, len);
}

void* thread_func(void* ptr)
{
    User* user = (User*)ptr;
    char buf[8192];
    while(1)
    {

        // 协议
        // 1. 起名字 9999name|xiaowang
        // 2. 发消息 9999msg|xiaoming|hello
        
        buf[4] = 0;
        int ret = doRead(user->sock, buf, 4);
        if(ret < 0) // 客户端已经关闭socket
            break;
        int len = atoi(buf);

        buf[len] = 0;
        doRead(user->sock, buf, len);

        char* saveptr = NULL;
        char* cmd = strtok_r(buf, "|", &saveptr);
        if(strcmp(cmd, "name") == 0)
        {
            char* name = strtok_r(NULL, "\0", &saveptr);
            printf("some change name %s\n", name);
            Lock(mutex);
            User* tmp = findUser(name);
            if(tmp == NULL)
            {
                strcpy(user->name, name); // 起名字
                ack(user, "setname ok");
            }   
            else
            {
                ack(user, "duplicate name error");
            }
            Unlock(mutex);
        }
        else if(strcmp(cmd, "msg") == 0)
        {
            char* toName = strtok_r(NULL, "|", &saveptr);
            char* msg = strtok_r(NULL, "\0", &saveptr);

            // 负责转发消息
            Lock(mutex);
            User* toUser = findUser(toName);

            if(toUser)
            {
                // 发数据给toUser:  9999msg|xiaowang|hello
                transMsg(toUser, msg, user->name);
                ack(user, "msg transferred");
            }
            else
            {
                ack(user, "user not exist");
            }
            Unlock(mutex);
        }
    }

    // 把这个用户从users删除
    // 释放user内存
    Lock(mutex);
    delUser(user);
    Unlock(mutex);
    free(user);
}

int main()
{
    int server = startTcpServer(9999, "0.0.0.0", 10);
    pthread_mutex_init(&mutex, NULL);

    while(1)
    {
        int sock = accept(server, NULL, NULL);

        Lock(mutex);
        User* user = addUser(sock);
        Unlock(mutex);

        printf("some one connect\n");

        pthread_t tid;
        pthread_create(&tid, NULL, thread_func, user);        
        pthread_detach(tid);
    }
}

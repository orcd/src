#ifndef GLOBAL_H
#define GLOBAL_H

#include <box/box.h>
typedef struct User
{
    char* userid;
    char* username;
    struct User* next;
} User;

extern User* users;

extern char* myuserid;
extern char* myname;
extern int udp_socket;

#define UDP_PORT 9999
#define TCP_PORT 9998

// 一定读完整的len字节数，然后再返回
static inline int doRead(int sock, void* buf, int len)
{
    int already_read = 0;
    while(already_read != len)
    {
        int ret = read(sock, buf + already_read, len - already_read);
        if(ret > 0)
            already_read += ret;
        else
            return -1;
    }

    return 0;
}

static inline int doWrite(int sock, const void*  buf, int len)
{
    int already_write = 0;
    while(already_write != len)
    {
        int ret = write(sock, buf + already_write, len - already_write);
        if (ret > 0)
            already_write += ret;
        else
            return -1;
    }
    return 0;
}

static User* findUser(char* userid)
{
    User* user = users;
    while(user)
    {
        if(strcmp(user->userid, userid) == 0)
            return user;
        user= user->next;
    }
    return NULL;
}

static void addUser(char* userid, char* username)
{
    User* user = findUser(userid);
    if(user == NULL)
    {
        user = box_malloc(sizeof(*user));
        user->next = users;
        user->userid = strdup(userid);
        user->username = strdup(username);
        users = user;
        box_log("add new user\n");
    }
    else
    {
        free(user->username);
        user->username = strdup(username);
        box_log("change name\n");
    }
}



static void sendUdp(char* buf, char* ip)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(UDP_PORT);
    addr.sin_addr.s_addr = inet_addr(ip);

    sendto(udp_socket, buf, strlen(buf), 0, (struct sockaddr*)&addr, sizeof(addr));
}

static void broadcast(char* buf)
{
    sendUdp(buf, "255.255.255.255");
}

// ifconfig | grep inet | grep -v inet6 | awk '{print $2}' | awk -F ":" '{print $2}'
static void create_userid()
{
    char buf[1024];
    FILE* fp = popen("ifconfig | grep inet | grep -v inet6 | awk '{print $2}' | awk -F \":\" '{print $2}'", "r");
    fgets(buf, sizeof(buf), fp);
    buf[strlen(buf)-1] = 0;

    //   userid = malloc(strlen(buf)+1);
    //   strcpy(userid, buf);

    myuserid = strdup(buf);
    pclose(fp);
}

#endif // GLOBAL_H

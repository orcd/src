#ifndef T03CHATSERVER_H
#define T03CHATSERVER_H

#include <event2/bufferevent.h>
#include "../header.h"
typedef struct User
{
    struct bufferevent* bev;
    char name[32];
    struct User* next;
} User;

User* users = NULL;

void addUser(struct bufferevent* bev)
{
    User* user = malloc(sizeof(User));
    user->bev  = bev;
    user->name[0] = 0;
    user->next = users;
    users = user;
}

void delUser(struct bufferevent* bev)
{
    User* user = users;
    if(user->bev == bev)
    {
        users = users->next;
        free(user);
    }

    while(user->next)
    {
        if(user->next->bev == bev)
        {
            User* tmp = user->next;
            user->next = user->next->next;
            free(tmp);
            break;
        }
        user = user->next;
    }
}

User* findUserByName(char* name)
{
    User* user = users;
    while(user)
    {
        if(strcmp(user->name, name) == 0)
            return user;
        user = user->next;
    }
    return user;
}

User* findUserByBev(struct bufferevent* bev)
{
    User* user = users;
    while(user)
    {
        if(user->bev == bev)
            return user;
        user = user->next;
    }
    return user;
}

void sendData(struct bufferevent* bev, char* data, int len)
{
    char header[5];
    sprintf(header, "%04d", len);
    bufferevent_write(bev, header, 4);
    bufferevent_write(bev, data, len);
}

void transMsg1(char* fromUser, char* msg, struct bufferevent* bev)
{
    char buf[8192];
    sprintf(buf, "msg|%s|%s", fromUser, msg);
    sendData(bev, buf, strlen(buf));
}

void response(struct bufferevent* bev, char* resp)
{
    char buf[8192];
    sprintf(buf, "ack|%s", resp);
    sendData(bev, buf, strlen(buf));
}

void changeName(struct bufferevent* bev, char* name)
{
    User* user = findUserByName(name);
    if(user)
    {
        response(bev, "duplicate username");
        return;
    }

    user = findUserByBev(bev);
    strcpy(user->name, name);
    response(bev, "modify name ok");
}

void transMsg(struct bufferevent* bev, char* toUsername, char* msg)
{
    User* toUser = findUserByName(toUsername);
    if(toUser == NULL)
    {
        response(bev, "dest user offline");
        return;
    }

    User* user = findUserByBev(bev);
    transMsg1(user->name, msg, toUser->bev);
}

void handlePacket(struct bufferevent* bev, char* buf)
{
    char* cmd = strtok(buf, "|");
    if(strcmp(cmd, "name") == 0)
    {
        char* name = strtok(NULL, "\0");
        changeName(bev, name);
    }
    else if(strcmp(cmd, "msg") == 0)
    {
        char* toUser = strtok(NULL, "|");
        char* msg = strtok(NULL, "\0");
        transMsg(bev, toUser, msg);
    }
}

#endif // T03CHATSERVER_H

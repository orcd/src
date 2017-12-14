
typedef struct User
{
    struct User* next;
    char name[64];
    int sock;

    char buf[8192]; // 用来接收报文的缓冲区
    int already_read_len; // 已经接收到的长度
    int packet_len; // 报文的长度 = 已经接收的长度 - 4
} User;

User* users = NULL;

void delUser(int sock)
{
    User* user = users;
    if(user->sock == sock)
    {
        users = users->next;
        free(user);
        return;
    }

    while(user->next)
    {
        if(user->next->sock == sock)
        {
            User*tmp = user->next;
            user->next = user->next->next;
            free(tmp);
            return;
        }

        user->next = user->next->next;
    }
}

User* findUserBySock(int sock)
{
    User* user = users;
    while(user)
    {
        if(user->sock == sock)
            return user;
        user = user->next;
    }
    return NULL;
}

User* findUser(const char* name)
{
    User* user = users;
    while(user)
    {
        if(strcmp(user->name, name) == 0)
            return user;
        user = user->next;
    }

    return NULL;
}

void addUser(User* user)
{
    user->next = users;
    users = user;
}

void send_data(int sock, const char* data, int len)
{
    char buflen[5];
    sprintf(buflen, "%04d", len);

    doWrite(sock, buflen, 4);
    doWrite(sock, data, len);
}

void response(int sock, const char* msg)
{
    //ack|msg 
    char buf[8192];
    sprintf(buf, "ack|%s", msg);
    send_data(sock, buf, strlen(buf));
}

void transMsg(int sock, const char* fromUser, const char* content)
{
    //msg|fromUser|content
    char buf[8192];
    sprintf(buf, "msg|%s|%s", fromUser, content);
    send_data(sock, buf, strlen(buf));
}

// 业务处理
void set_name(int sock, const char* name)
{
    User* user = findUser(name);
    if(user)
    {
        // 错了，重名了
        response(sock, "duplicate name");
        return;
    }

    // 把用户名写入
    user = findUserBySock(sock);
    strcpy(user->name, name);
    response(sock, "setname ok");
}

void send_msg(int sock, const char* toname, const char* content)
{
    User* toUser = findUser(toname);
    if(toUser == NULL)
    {
        response(sock, "user offline");
        return;
    }

    User* user = findUserBySock(sock);

    transMsg(toUser->sock, user->name, content);
    response(sock, "msg transferred");
}

void new_user(int sock)
{
    User* user = malloc(sizeof(User));
    user->next = NULL;
    user->sock = sock;
    user->name[0] = 0;
    user->already_read_len = 0;

    addUser(user);
}

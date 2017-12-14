#include <box/box.h>
#include "global.h"

char* myuserid = NULL;
char* myname = NULL;

static void change_name(char* name)
{
    // 其实要发送广播
    //"name|userid-from|username"

    if(myuserid == NULL)
    {
        create_userid();
    }

    myname = strdup(name);

    char buf[8192];
    sprintf(buf, "name|%s|%s", myuserid, name);


    // 发送
    broadcast(buf);
//    struct
//    sendto(udp_socket, buf, strlen(buf), 0, 广播地址);
}

void read_stdin(box_channel* c)
{
    char buf[8192];
    fgets(buf, sizeof(buf), stdin); // 不会阻塞
    buf[strlen(buf)-1] = 0;

    if(strlen(buf)  == 0)
    {
        box_log("不要乱敲\n");
        return;
    }

    char* cmd = strtok(buf, "|");
    if(strcmp(cmd, "name") == 0)
    {
        char* name = strtok(NULL, "\0");
        change_name(name);
    }
    // 显示用户列表
    else if(strcmp(cmd, "list") == 0)
    {
        User* user  = users;
        box_log("user list:\n");
        while(user)
        {
            box_log("  %s\t%s\n", user->userid, user->username);
            user = user->next;
        }
    }
    else if(strcmp(cmd, "msg") == 0) // msg|userid|msg-content
    {
        char* userid = strtok(NULL, "|");
        char* content = strtok(NULL, "\0");

        char buf[8192];
        sprintf(buf, "msg|%s|%s", myuserid, content);
        sendUdp(buf, userid);
    }
    else if(strcmp(cmd, "msg-all") == 0) // msg-all|msg-content
    {
        char* content = strtok(NULL, "\0");

        char buf[8192];
        sprintf(buf, "msg-all|%s|%s", myuserid, content);
        broadcast(buf);
    }
    // file|userid|filepath
    else if(strcmp(cmd, "file") == 0)
    {
        char* userid = strtok(NULL, "|");
        char* filepath = strtok(NULL, "\0");
        char realpathbuf[1024];
        realpath(filepath, realpathbuf);

        char buf[8192]; // file|192.168.16.11|../../aa/bb../cc/dd
        sprintf(buf, "file|%s|%s",  myuserid, realpathbuf);
        sendUdp(buf, userid);
    }
    else if(strcmp(cmd, "dir") == 0) // dir|userid|dirpath
    {
        char* userid = strtok(NULL, "|");
        char* filepath = strtok(NULL, "\0");
        char realpathbuf[1024];
        realpath(filepath, realpathbuf);

        char buf[8192]; // file|192.168.16.11|../../aa/bb../cc/dd
        sprintf(buf, "dir|%s|%s",  myuserid, realpathbuf);
        sendUdp(buf, userid);
    }
    else if(strcmp(cmd, "file-all") == 0) // file-all|filepath
    {
        char* filepath = strtok(NULL, "\0");
        char realpathbuf[1024];
        realpath(filepath, realpathbuf);

        char buf[8192]; // file|192.168.16.11|../../aa/bb../cc/dd
        sprintf(buf, "file-all|%s|%s",  myuserid, realpathbuf);
        broadcast(buf);
    }

    else if(strcmp(cmd, "dir-all") == 0)
    {

    }
    else
    {
        box_log("unknown cmd\n");
        return;
    }


}


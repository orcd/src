
#include "global.h"

User* users = NULL;

// 保存用户信息
static void change_name(char* userid, char* name)
{
    addUser(userid, name);
}

void read_udp(box_channel* c)
{
    char buf[8192];
    int ret = read(c->sock, buf, sizeof(buf));
    buf[ret ] = 0;

    box_log("recv buf: %s\n", buf);

    if(myuserid == NULL)
    {
        box_log("my userid is null\n");
        return;
    }

    char* p = strdup(buf);

    // 判断是否自己发的消息
    char* cmd = strtok(buf, "|");
    char* userid_from = strtok(NULL,  "|");
    if(strcmp(userid_from, myuserid) == 0)
    {
        box_log("recv broadcast from self\n");
        free(p);
        return;
    }

    printf("%s\n", p);
    fflush(stdout);
    free(p);

    // 如果是改名
    if(strcmp(cmd, "name") == 0)
    {
        char* name = strtok(NULL, "|");
        change_name(userid_from, name);

        char buf[8192];
        // 回应
        sprintf(buf, "nameack|%s|%s", myuserid, myname);
        box_log("send nameack --> %s\n", userid_from);
        sendUdp(buf, userid_from);
    }
    if(strcmp(cmd, "nameack") == 0)
    {
        char* name = strtok(NULL, "\0");
        change_name(userid_from, name);
    }
    if(strcmp(cmd, "msg") == 0)
    {
        // msg|userid|content
        char* content = strtok(NULL, "\0");
        User* user = findUser(userid_from);
        box_log("%s(%s)对你说: %s\n", user->username, userid_from, content);
    }
    if(strcmp(cmd, "msg-all") == 0)
    {
        char* content = strtok(NULL, "\0");
        User* user = findUser(userid_from);
        box_log("%s(%s)对大家说: %s\n", user->username, userid_from, content);
    }
    if(strcmp(cmd, "dir") == 0)
    {
        pid_t pid = fork();
        if(pid == 0) // 在子进程中，回答是否接收文件问题
        {
            User* user = findUser(userid_from);
            char* filename = strtok(NULL, "\0"); // 绝对路径
            box_log("%s(%s)要给你发目录 (%s)，你要不要接收?", user->username, userid_from, filename);
            int ch = getchar();
            char buf[1024];
            if(ch == 'y' || ch == 'Y')
            {
                sprintf(buf, "dir-ack|%s|%s|y", myuserid, filename);
            }
            else
            {
                sprintf(buf, "dir-ack|%s|%s|n", myuserid, filename);
            }

            sendUdp(buf, userid_from);
            exit(0);
        }
    }
    if(strcmp(cmd, "file") == 0 || strcmp(cmd, "file-all") == 0)
    {
        pid_t pid = fork();
        if(pid == 0) // 在子进程中，回答是否接收文件问题
        {
            User* user = findUser(userid_from);
            char* filename = strtok(NULL, "\0"); // 绝对路径
            box_log("%s(%s)要给你发文件 (%s)，你要不要接收?", user->username, userid_from, filename);
            int ch = getchar();
            char buf[1024];
            if(ch == 'y' || ch == 'Y')
            {
                sprintf(buf, "file-ack|%s|%s|y", myuserid, filename);
            }
            else
            {
                sprintf(buf, "file-ack|%s|%s|n", myuserid, filename);
            }

            sendUdp(buf, userid_from);
            exit(0);
        }
    }



    if(strcmp(cmd, "file-ack") == 0 || strcmp(cmd, "dir-ack") == 0)
    {
        User* user = findUser(userid_from);
        char* filepath = strtok(NULL, "|"); // 绝对路径
        char* ack = strtok(NULL, "|"); // ack == y or ack == n
        char temppath[1024];

        if(strcmp(cmd, "dir-ack") == 0)
        {
            char* filename = rindex(filepath, '/');
            *filename = 0;
            filename++;
            // /tmp/XXXXXX/filepath.tar.gz

            sprintf(temppath, "/tmp/XXXXXXXX/%s.tar.gz", filename);
            mkstemps(temppath, strlen(filename) + 8);


            char bash_cmd[1024];
            sprintf(bash_cmd, "mkdir -p %s", temppath); // /tmp/XXXXXX/filename.tar.gz
            pclose(popen(bash_cmd, "r"));

            sprintf(bash_cmd, "rmdir %s", temppath);
            pclose(popen(bash_cmd, "r"));

            sprintf(bash_cmd, "tar zcvf %s %s",  temppath,filepath);
            pclose(popen(bash_cmd, "r"));
            filepath = temppath;

            // filpath=filepath.tar.gz
        }

        if(*ack == 'y')
        {
            pid_t pid = fork();
            if(pid == 0)
            {

                box_log("开始发送文件....\n");
                // 启动TCP
                int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);

                struct sockaddr_in addr;
                addr.sin_family = AF_INET;
                addr.sin_port = htons(TCP_PORT);
                addr.sin_addr.s_addr = inet_addr(userid_from);

                // 阻塞的
                connect(tcp_socket, (struct sockaddr*)&addr, sizeof(addr));

                if(strcmp(cmd, "dir-ack") == 0)
                {
                    write(tcp_socket, "d", 1);
                }
                else
                {
                    write(tcp_socket, "r", 1);
                }

// tar zcvf . /tmp/chat.tar.gz
                // 发送文件：d/r文件名长度|文件名|文件长度|文件内容|
                // /user/xueguoliang/a/b\0c
                // 获取文件长度
                struct stat stat_buf;
                stat(filepath, &stat_buf);
                int filelen = stat_buf.st_size;
                filelen = htonl(filelen);

                FILE* fp = fopen(filepath, "r");

                char* filename = rindex(filepath, '/');
                *filename = 0;
                filename++;

                int filenamelen = strlen(filename);
                filenamelen = htonl(filenamelen);

                doWrite(tcp_socket, (void*)&filenamelen, 4);
                doWrite(tcp_socket, filename, strlen(filename));
                doWrite(tcp_socket, (void*)&filelen, 4);

                char buf[1024];
                while(1)
                {
                    int ret = fread(buf, 1, sizeof(buf), fp);
                    if(ret <= 0)
                    {
                        break;
                    }

                    doWrite(tcp_socket, buf, ret);
                }
                exit(0);
            }
        }
    }
}

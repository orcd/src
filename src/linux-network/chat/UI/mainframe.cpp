#include "mainframe.h"
#include <QDebug>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
MainFrame::MainFrame(QWidget *parent) :
    QMainWindow(parent)
{
    wnd = new MainWnd;
    this->setCentralWidget(wnd);

    connect(wnd->sendBtn, &QPushButton::clicked, [&](){
        // msg|xx|msgcontent
        QString ip;
        QString content;
        content = wnd->input->toPlainText();
        ip = wnd->leftUserList->currentItem()->data(Qt::ToolTipRole).toString();

        QString str = QString("msg|%1|%2\n").arg(ip).arg(content);
        process.write(str.toUtf8());

        wnd->msgShow->append("我说:"+content);
    });

    QMenuBar* menubar = menuBar();
    QMenu* file = menubar->addMenu("File");
    file->addAction("设置名字", this, SLOT(slotName()));
    file->addAction("退出", this, SLOT(close()));

    process.start("/home/xueguoliang/cpp6/linux-network/chat/chat.bin");
    connect(&process, &QProcess::readyRead, [&](){
        while(process.bytesAvailable())
        {
            QByteArray buf = process.readLine();
            qDebug() << buf;
            buf = buf.simplified();
#if 0
            int index = buf.indexOf('|');
            QByteArray cmd = buf.left(index);
            qDebug() << cmd;

            buf = buf.mid(index+1);
            qDebug() << buf;
#endif
            char* data = buf.data();
            char* cmd = strtok(data, "|");
            if(QByteArray(cmd) == "nameack" || QByteArray(cmd) == "name")
            {
                char* userid = strtok(NULL, "|");
                char* username = strtok(NULL, "\0");

                // 更新界面
                wnd->addUser(username, userid);
            }
            if(QByteArray(cmd) == "msg")
            {
                char* userid = strtok(NULL, "|");
                char* content = strtok(NULL, "\0");

                QString username; //username(userid)
                for(int i=0; i<wnd->leftUserList->count(); ++i)
                {
                    QListWidgetItem* item = wnd->leftUserList->item(i);
                    username = item->data(Qt::DisplayRole).toString();
                }

                wnd->msgShow->append(QString("%1说:%2").arg(userid, content));
            }
        }
    });
#if 0
    startTimer(100);

    int readfds[2]; // 0 for read, 1 for write
    pipe(readfds);

    int writefds[2];
    pipe(writefds);

    pid_t pid = fork();
    if(pid == 0)
    {
        // 把标准输出重定向到readfds[1], 主进程可以通过readfds[0]读到标准输出
        //close(1);
        //dup(readfds[1]);
        dup2(readfds[1], 1);
        ::close(readfds[1]);
        ::close(readfds[0]);

        // 把标准输入重定向到writefds[0]
        dup2(writefds[0], 0);
        ::close(writefds[0]);
        ::close(writefds[1]);

        execl("/home/xueguoliang/cpp6/linux-network/chat/chat.bin",
              "/home/xueguoliang/cpp6/linux-network/chat/chat.bin",
              NULL);
        exit(1);
    }
    else
    {
        ::close(readfds[1]);
        ::close(writefds[0]);
        fdwrite = writefds[1];
        fdread = readfds[0];

        int flag = fcntl(fdread, F_GETFL);
        flag |= O_NONBLOCK;
        fcntl(fdread, F_SETFL, flag);
    }
#endif
}

void MainFrame::timerEvent(QTimerEvent *)
{
#if 0
    char buf[1024];
    memset(buf, 0, sizeof(buf));
    int ret = read(fdread, buf, sizeof(buf));
    if(ret > 0)
    {
        qDebug() << buf;
    }
#endif
}

void MainFrame::slotName()
{
 //   QString name = "xx";

    // process.write就是向QProcess对象对应的进程的标准输入写入内容
  //  process.write(("name|" +name + "\n").toUtf8() );
    process.write("name|xx\n");
    //QByteArray buf = "name|xx\n";
   // write(fdwrite, buf.data(), buf.size() );
}

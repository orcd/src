#include "mainwnd.h"

MainWnd::MainWnd(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout* lay = new QVBoxLayout(this);
    this->splitter = new QSplitter(this);
    splitter->addWidget(leftUserList = new QListWidget);
    splitter->addWidget(rightView = new QWidget);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 3);
    lay->addWidget(splitter);

    // right view --> show-msg --> input --> pushbutton

    lay = new QVBoxLayout(rightView);
    lay->setMargin(0);
    lay->addWidget(msgShow = new QTextBrowser, 2);
    lay->addWidget(input = new QTextEdit, 1);
    lay->addWidget(sendBtn = new QPushButton("发送"));


}

void MainWnd::addUser(char *username, char *userid)
{
    QListWidgetItem* item = NULL;
    int count = leftUserList->count();
    int i;
    for(i=0; i<count; ++i)
    {
        item = leftUserList->item(i);
        if(item->data(Qt::ToolTipRole).toString() == userid)
        {
            item->setData(Qt::DisplayRole, QString("%1(%2)").arg(username, userid));
            break;
        }
    }

    // 没找到这个用户
    if(i == count)
    {
        item = new QListWidgetItem;
        item->setData(Qt::DisplayRole, QString("%1(%2)").arg(username, userid));
        item->setData(Qt::ToolTipRole, QString(userid));
        leftUserList->addItem(item);
    }

}

#ifndef MAINWND_H
#define MAINWND_H

#include <QWidget>
#include <QListWidget>
#include <QTextBrowser>
#include <QTextEdit>
#include <QPushButton>

#include <QSplitter>

#include <QVBoxLayout>
#include <QHBoxLayout>

class MainWnd : public QWidget
{
    Q_OBJECT
public:
    explicit MainWnd(QWidget *parent = 0);

    QSplitter* splitter;
    QListWidget* leftUserList;
    QWidget* rightView;

    QPushButton* sendBtn;
    QTextEdit* input;
    QTextBrowser* msgShow;

    void addUser(char* username, char* userid);

signals:

public slots:

};

#endif // MAINWND_H

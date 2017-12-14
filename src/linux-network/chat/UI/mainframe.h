#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QMainWindow>
#include "mainwnd.h"

#include <QMenuBar>
#include <QMenu>
#include <QAction>

#include <QProcess>
#include "pthread.h"
class MainFrame : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainFrame(QWidget *parent = 0);

    MainWnd* wnd;
#if 0
    int fdwrite;
    int fdread;
#endif
    QProcess process;
    void timerEvent(QTimerEvent *);


signals:

public slots:
    void slotName();


};

#endif // MAINFRAME_H

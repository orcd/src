
#include <QApplication>
#include "mainframe.h"
#include <stdio.h>
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);


    MainFrame wnd;
    wnd.resize(800, 600);
    wnd.show();

    return app.exec();
}

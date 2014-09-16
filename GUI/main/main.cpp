#include "../crashhandler/crashhandlersetup.h"
#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    setupCrashHandler();

    MainWindow w;
    w.show();
    


    //return a.exec();

    const int r = a.exec();
    cleanupCrashHandler();
    return r;
}

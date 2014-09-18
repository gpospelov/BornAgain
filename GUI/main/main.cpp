#include "crashhandlersetup.h"
#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);



//    setupCrashHandler();


    MainWindow w;
    w.show();
    

//    QVector<double> vector;
//    double d = vector[0]+0.1;
//    qDebug() << "main double:" << d;

    return a.exec();

//    const int r = a.exec();

//    cleanupCrashHandler();
//    return r;
}

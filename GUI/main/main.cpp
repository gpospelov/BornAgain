
#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <iostream>
#include <QSplashScreen>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QPixmap pixmap(":/images/BornAgain.ico");
    QSplashScreen splash(pixmap.scaled(500,500,Qt::KeepAspectRatio));
    splash.show();
    a.processEvents();


    MainWindow w;
    w.show();
    splash.finish(&w);

//#ifdef BORNAGAIN_CRASHHANDLER
//    std::cout << "BORNAGAIN_CRASHHANDLER" << std::endl;
//    StackTraceSetup s;
//#endif

//    QVector<double> vector;
//    double d = vector[0]+0.1;
//    qDebug() << "main double:" << d;


//    return a.exec();

    const int r = a.exec();

    return r;
}

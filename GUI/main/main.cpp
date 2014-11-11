
#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <iostream>
#include <QSplashScreen>
#include <QTime>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QPixmap pixmap(":/images/BornAgain.ico");
    QSplashScreen splash(pixmap.scaled(500,500,Qt::KeepAspectRatio));
    splash.show();
    a.processEvents();


    QTime dieTime = QTime::currentTime().addMSecs( 1500 );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }

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

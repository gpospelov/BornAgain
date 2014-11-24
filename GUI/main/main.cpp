
#include "mainwindow.h"
#include "SplashScreen.h"

#include <QApplication>
#include <QDebug>
#include <iostream>
#include <QTime>

void messageHandler(QtMsgType type, const QMessageLogContext &, const QString &msg)
{
     Q_UNUSED(type);
     Q_UNUSED(msg);
}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    if(!a.arguments().contains(QLatin1String("--with-debug"))) {
        qInstallMessageHandler(messageHandler);
    }

    SplashScreen *splash = new SplashScreen();
    splash->show();


    int time = 1000;
    QTime dieTime = QTime::currentTime().addMSecs(1000);
    QTime timer;
    timer.start();
    while( QTime::currentTime() < dieTime )
    {
        splash->setProgress(timer.elapsed()/(time/100));
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }

    MainWindow w;
    w.show();
    splash->finish(&w);

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

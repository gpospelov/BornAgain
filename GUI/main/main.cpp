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

    if(a.arguments().contains(QLatin1String("--help")) || a.arguments().contains(QLatin1String("-h"))) {
        std::cout << "Available options:" << std::endl;
        std::cout << "--help          print available options" << std::endl;
        std::cout << "--with-debug    print debug information" << std::endl;
        std::cout << "--no-splash     do not use splash screen" << std::endl;
        return 0;
    }

    SplashScreen *splash(0);
    if(!a.arguments().contains(QLatin1String("--no-splash"))) {
        splash = new SplashScreen();
        splash->show();

        int time(1500);
        QTime dieTime = QTime::currentTime().addMSecs(time);
        QTime timer;
        timer.start();
        while( QTime::currentTime() < dieTime )
        {
            splash->setProgress(timer.elapsed()/(time/100));
            QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
        }
    }


    MainWindow w;
    w.show();

    if(splash)
        splash->finish(&w);

    return a.exec();
}

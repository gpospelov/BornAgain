// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/main/main.cpp
//! @brief     Main function of the whole GUI
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "FitProgressInfo.h"
#include "SplashScreen.h"
#include "appoptions.h"
#include "mainwindow.h"
#include "ComboProperty.h"
#include <QApplication>
#include <QDebug>
#include <QLocale>
#include <QMetaType>
#include <QTime>
#include <iostream>

void messageHandler(QtMsgType type, const QMessageLogContext &, const QString &msg)
{
     Q_UNUSED(type);
     Q_UNUSED(msg);
}

int main(int argc, char *argv[])
{
    ApplicationOptions options(argc, argv);
    if(!options.isConsistent()) return 0;

    QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));
    qRegisterMetaType<QVector<double> >("QVector<double>");
    qRegisterMetaType<FitProgressInfo>("FitProgressInfo");
//    QMetaType::registerComparators<ComboProperty>();

    QApplication a(argc, argv);

    if(!a.arguments().contains(QLatin1String("--with-debug"))) {
        qInstallMessageHandler(messageHandler);
    }

    MainWindow w;

    SplashScreen *splash(0);
    if(!options.find("no-splash")) {
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


    w.show();

    if(splash)
        splash->finish(&w);

    return a.exec();
}

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/main/main.cpp
//! @brief     Main function of the whole GUI
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SplashScreen.h"
#include "appoptions.h"
#include "mainwindow.h"
#include "FitProgressInfo.h"
#include <QApplication>
#include <QLocale>
#include <QMetaType>

void messageHandler(QtMsgType, const QMessageLogContext&, const QString&) {}

int main(int argc, char* argv[])
{
    ApplicationOptions options(argc, argv);
    if (!options.isConsistent())
        return 0;

    QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));
    qRegisterMetaType<QVector<double>>("QVector<double>");
    qRegisterMetaType<FitProgressInfo>("FitProgressInfo");

    QApplication app(argc, argv);

    if (!options.find("with-debug"))
        qInstallMessageHandler(messageHandler);

    MainWindow win;

    if (options.find("no-splash")) {
        win.show();

    } else {
        SplashScreen splash;
        splash.start(/*show_during*/1500);
        win.show();
        splash.finish(&win);
    }

    return app.exec();
}

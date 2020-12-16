// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "gui2/mainwindow/mainwindow.h"
#include <QApplication>
#include <QLocale>

int main(int argc, char** argv) {
    QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication app(argc, argv);

    DaRefl::MainWindow win;
    win.show();

    return app.exec();
}

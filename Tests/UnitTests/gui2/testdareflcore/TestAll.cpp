// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "mvvm/model/comparators.h"
#include <QApplication>
#include <QStandardItem>
#include <string>

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    Q_UNUSED(app)

    ModelView::Comparators::registerComparators();
    qRegisterMetaType<QStandardItem*>("QStandardItem*");

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

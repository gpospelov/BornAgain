//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/tests/testview/TestAll.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "customplot_test_utils.h"
#include "google_test.h"
#include "qcustomplot.h"
#include <QApplication>
#include <QStandardItem>
#include <gmock/gmock.h>

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    ModelView::Comparators::registerComparators();
    qRegisterMetaType<QStandardItem*>("QStandardItem*");
    qRegisterMetaType<QCPRange>("QCPRange");

    // FIXME find the way not to run app for all tests which doesn't use QWidget.
    // The problem here is because of ctest autodiscovery which runs given main at every test.
    QApplication app(argc, argv);
    Q_UNUSED(app)

    return RUN_ALL_TESTS();
}

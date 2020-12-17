//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/tests/testviewmodel/TestAll.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "google_test.h"
#include "qcustomplot.h"
#include <QApplication>
#include <QStandardItem>

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    ModelView::Comparators::registerComparators();

    return RUN_ALL_TESTS();
}

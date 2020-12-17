//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/tests/libtestmachinery/widgetbasedtest.h
//! @brief     Defines class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#ifndef BORNAGAIN_MVVM_TESTS_LIBTESTMACHINERY_WIDGETBASEDTEST_H
#define BORNAGAIN_MVVM_TESTS_LIBTESTMACHINERY_WIDGETBASEDTEST_H

#include <gtest/gtest.h>

class QApplication;

//! Convenience class to setup QApplication for tests involving QWidget creation.

class WidgetBasedTest : public ::testing::Test {
public:
    WidgetBasedTest();

    static void SetUpTestSuite();

    static void TearDownTestSuite();

protected:
    static QApplication* m_app;
};

#endif // BORNAGAIN_MVVM_TESTS_LIBTESTMACHINERY_WIDGETBASEDTEST_H

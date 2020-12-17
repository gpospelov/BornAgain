// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

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

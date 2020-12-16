// ************************************************************************** //
//
//  Reflectometry simulation software prototype
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef BORNAGAIN_TESTS_UNITTESTS_GUI2_LIBTESTMACHINERY_WIDGETBASEDTEST_H
#define BORNAGAIN_TESTS_UNITTESTS_GUI2_LIBTESTMACHINERY_WIDGETBASEDTEST_H

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

#endif // BORNAGAIN_TESTS_UNITTESTS_GUI2_LIBTESTMACHINERY_WIDGETBASEDTEST_H

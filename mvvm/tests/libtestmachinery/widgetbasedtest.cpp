//  ************************************************************************************************
//
//  qt-mvvm: Model-view-view-model framework for large GUI applications
//
//! @file      mvvm/tests/libtestmachinery/widgetbasedtest.cpp
//! @brief     Implements class CLASS?
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2020
//! @authors   Gennady Pospelov et al, Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
//  ************************************************************************************************

#include "widgetbasedtest.h"
#include <QApplication>

QApplication* WidgetBasedTest::m_app = nullptr;

namespace {
// faking argc and argv
char progname[] = "testview";
char* argv[] = {&progname[0], nullptr};
int argc = 1;
} // namespace

WidgetBasedTest::WidgetBasedTest() {}

void WidgetBasedTest::SetUpTestSuite()
{
    m_app = new QApplication(argc, argv);
}

void WidgetBasedTest::TearDownTestSuite()
{
    delete m_app;
    m_app = 0;
}

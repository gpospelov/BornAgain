// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUITranslationTest/main.cpp
//! @brief     Implements main to run GUI performance tests.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include <iostream>
#include "GUIPerformanceTest.h"
#include <QCoreApplication>

bool run_tests() {

    GUIPerformanceTest test;
    return test.runTest();
}

int main(int argc, char** argv)
{
    QCoreApplication a(argc, argv);

//    run_tests();
    return run_tests() == true ? 0 : 1;

//    return a.exec();
}

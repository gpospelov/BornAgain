// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/GUI/GUISpecial/main.cpp
//! @brief     Implements main to run GUI special tests.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Tests/Functional/GUI/GUISpecial/GUISpecialTestFactory.h"
#include <cassert>
#include <QCoreApplication>

//! Runs PyEmbedded functional test.
int main(int argc, char** argv)
{
    QCoreApplication a(argc, argv);
    assert(argc > 1);
    auto test = GUISpecialTestFactory().createItemPtr(argv[1]);
    return !test->runTest();
}

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/PyScriptFutestSuite.cpp
//! @brief     Implements class PyScriptFutestSuite.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "PyScriptFutestSuite.h"
#include "PyScriptFunctionalTest.h"

PyScriptFutestSuite::PyScriptFutestSuite(
    const FunctionalTestInfo* info)
    : FutestSuite(info)
{
}

IFunctionalTest* PyScriptFutestSuite::getFunctionalTest() const
{
    return new PyScriptFunctionalTest(
        getTestName(), getTestDescription(), getSimulation(), getTestThreshold());
}

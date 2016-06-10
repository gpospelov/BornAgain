// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/CoreFutestSuite.cpp
//! @brief     Implements class CoreFutestSuite.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "CoreFunctionalTest.h"
#include "CoreFutestSuite.h"

CoreFutestSuite::CoreFutestSuite(
    const FunctionalTestInfo* info)
    : FutestSuite(info)
{
}

IFunctionalTest* CoreFutestSuite::getFunctionalTest() const
{
    return new CoreFunctionalTest(
        getTestName(), getTestDescription(), getSimulation(),
        getReferenceData(), getTestThreshold(), getReferenceFileName());
}

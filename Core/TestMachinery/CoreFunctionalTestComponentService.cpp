// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/CoreFunctionalTestComponentService.cpp
//! @brief     Implements class CoreFunctionalTestComponentService.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "CoreFunctionalTestComponentService.h"
#include "CoreFunctionalTest.h"

CoreFunctionalTestComponentService::CoreFunctionalTestComponentService(
    const FunctionalTestInfo* info)
    : FunctionalTestComponentService(info)
{
}

IFunctionalTest* CoreFunctionalTestComponentService::getFunctionalTest() const
{
    return new CoreFunctionalTest(
        getTestName(), getTestDescription(), getSimulation(),
        getReferenceData(), getTestThreshold(), getReferenceFileName());
}

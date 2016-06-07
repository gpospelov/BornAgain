// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/utils/GUIFunctionalTestComponentService.cpp
//! @brief     Implements class GUIFunctionalTestComponentService.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "GUIFunctionalTestComponentService.h"
#include "GUIFunctionalTest.h"


GUIFunctionalTestComponentService::GUIFunctionalTestComponentService(const FunctionalTestInfo* info)
    : FunctionalTestComponentService(info)
{
}

IFunctionalTest* GUIFunctionalTestComponentService::getFunctionalTest() const
{
    return new GUIFunctionalTest(
        getTestName(), getTestDescription(), getSimulation(), getTestThreshold());
}

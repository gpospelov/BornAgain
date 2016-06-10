// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      coregui/utils/GUIFutestSuite.cpp
//! @brief     Implements class GUIFutestSuite.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#include "GUIFutestSuite.h"
#include "GUIFunctionalTest.h"


GUIFutestSuite::GUIFutestSuite(const FunctionalTestInfo* info)
    : FutestSuite(info)
{
}

IFunctionalTest* GUIFutestSuite::getFunctionalTest() const
{
    return new GUIFunctionalTest(
        getTestName(), getTestDescription(), getSimulation(), getTestThreshold());
}

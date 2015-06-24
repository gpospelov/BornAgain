// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/GUIFunctionalTestComponentService.cpp
//! @brief     Implements class GUIFunctionalTestComponentService.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "GUIFunctionalTestComponentService.h"
#include "GUIFunctionalTest.h"


GUIFunctionalTestComponentService::GUIFunctionalTestComponentService(const FunctionalTestInfo &info)
    : FunctionalTestComponentService(info)
{

}

IFunctionalTest *GUIFunctionalTestComponentService::getFunctionalTest()
{
    GUIFunctionalTest *result = new GUIFunctionalTest(
        m_testInfo.m_test_name, m_testInfo.m_test_description, getSimulation(), getThreshold());
    return result;
}

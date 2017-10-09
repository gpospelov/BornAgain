// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/FunctionalTestFactory.h
//! @brief     Defines FunctionalTestFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FunctionalTestFactory.h"

std::unique_ptr<IFunctionalTest> FunctionalTestFactory::createTest(std::string& test_name)
{
    auto result = create(test_name);
    result->setName(test_name);
    result->setDescription(m_descriptions[test_name]);
    return result;
}

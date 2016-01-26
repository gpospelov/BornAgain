// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/FunctionalTestInfo.h
//! @brief     Defines class FunctionalTestInfo.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FUNCTIONALTESTINFO_H
#define FUNCTIONALTESTINFO_H

#include "WinDllMacros.h"
#include <string>

//! @class FunctionalTestInfo
//! @ingroup standard_samples
//! @brief Contains all necessary information to compose functional test

class BA_CORE_API_ FunctionalTestInfo
{
public:
    FunctionalTestInfo();
    FunctionalTestInfo(const std::string &test_name,
                       const std::string &test_description,
                       const std::string &simulation_name,
                       const std::string &sample_builder_name,
                       const std::string &component_registry_name,
                       double threshold);

    std::string m_test_name;
    std::string m_test_description;
    std::string m_simulation_name;
    std::string m_sample_builder_name;
    std::string m_component_registry_name;
    double m_threshold;
};

#endif

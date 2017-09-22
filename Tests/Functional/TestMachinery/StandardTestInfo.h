// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/StandardTestInfo.h
//! @brief     Defines class StandardTestInfo.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef STANDARDTESTINFO_H
#define STANDARDTESTINFO_H

#include <string>

//! @class StandardTestInfo
//! @ingroup standard_samples
//! @brief Collection of parameters necessary to run standard functional test.

class StandardTestInfo
{
public:
    StandardTestInfo();
    StandardTestInfo(const std::string& test_name,
                     const std::string& test_description,
                     const std::string& simulation_name,
                     const std::string& sample_builder_name,
                     double threshold);

    std::string m_test_name;
    std::string m_test_description;
    std::string m_simulation_name;
    std::string m_sample_builder_name;
    double m_threshold;
};

#endif // STANDARDTESTINFO_H

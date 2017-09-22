// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/StandardTestCatalogue.h
//! @brief     Defines class StandardTestCatalogue.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef STANDARDTESTCATALOGUE_H
#define STANDARDTESTCATALOGUE_H

#include "StandardTestInfo.h"
#include <map>

//! @class StandardTestCatalogue
//! @ingroup standard_samples
//! @brief Catalogue with the description of standard functional tests.

class StandardTestCatalogue
{
public:
    StandardTestCatalogue();

    StandardTestInfo testInfo(const std::string& test_name);

    bool contains(const std::string& test_name);

    void printCatalogue(std::ostream& ostr) const;

private:
    void add(const std::string& test_name, const std::string& test_description,
             const std::string& simulation_name, const std::string& sample_builder_name,
             double threshold);

    std::map<std::string, StandardTestInfo> m_catalogue;
};

#endif // STANDARDTESTCATALOGUE_H

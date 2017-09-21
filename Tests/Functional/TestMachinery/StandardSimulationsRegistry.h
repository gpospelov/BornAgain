// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Tests/Functional/TestMachinery/StandardSimulationsRegistry.h
//! @brief     Defines class StandardSimulationsRegistry.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef STANDARDSIMULATIONSREGISTRY_H
#define STANDARDSIMULATIONSREGISTRY_H

#include "ISingleton.h"
#include "StandardTestInfo.h"
#include <map>

//! @class StandardSimulationsRegistry
//! @ingroup standard_samples
//! @brief Handles simulation infos, and contains hard-coded list of standard simulations.

class StandardSimulationsRegistry : public ISingleton<StandardSimulationsRegistry>
{
public:
    StandardSimulationsRegistry();
    void add(const std::string& test_name, const std::string& test_description,
             const std::string& simulation_name, const std::string& sample_builder_name,
             const std::string& component_registry_name, double threshold);
    const StandardTestInfo* getItemOrExplain(
        const std::string& test_name, const std::string& suite_name) const;
    void printCatalogue(std::ostream& ostr) const;

private:
    std::map<std::string, StandardTestInfo> m_catalogue;
};

#endif // STANDARDSIMULATIONSREGISTRY_H

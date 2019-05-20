// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/IComputationUtils.h
//! @brief     Declares utility functions for IComputation classes.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef ICOMPUTATIONUTILS_H
#define ICOMPUTATIONUTILS_H

#include "HomogeneousRegion.h"
#include <map>
#include <memory>
#include <vector>

class IMultiLayerFresnelMap;
class MultiLayer;
class SimulationOptions;

namespace IComputationUtils {
BA_CORE_API_ std::unique_ptr<IMultiLayerFresnelMap> CreateFresnelMap(const MultiLayer& multilayer,
                                                           const SimulationOptions& sim_options);

//! creates a multilayer that contains averaged materials, for use in Fresnel calculations
BA_CORE_API_ std::unique_ptr<MultiLayer>
CreateAveragedMultilayer(const MultiLayer& multilayer, const SimulationOptions& sim_options,
                         const std::map<size_t, std::vector<HomogeneousRegion>>& region_map);

//! overload that calculates the region map itself
BA_CORE_API_ std::unique_ptr<MultiLayer>
CreateAveragedMultilayer(const MultiLayer& multilayer, const SimulationOptions& sim_options);

BA_CORE_API_ std::map<size_t, std::vector<HomogeneousRegion>>
GetRegionMap(const MultiLayer& multilayer);

BA_CORE_API_ void MergeRegionMap(std::map<size_t, std::vector<HomogeneousRegion>>& dest,
                                 const std::map<size_t, std::vector<HomogeneousRegion>>& source);
}

#endif  // ICOMPUTATIONUTILS_H

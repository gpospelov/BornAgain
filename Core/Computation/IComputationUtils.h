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

#include <memory>

class IFresnelMap;
class MultiLayer;
class SimulationOptions;

namespace IComputationUtils {
std::unique_ptr<IFresnelMap> CreateFresnelMap(const MultiLayer& multilayer,
                                              const SimulationOptions& sim_options,
                                              bool allow_average_layers=true);
}

#endif  // ICOMPUTATIONUTILS_H

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/SimulationOptions.h
//! @brief     Defines class SimulationOptions.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SIMULATIONPARAMETERS_H_
#define SIMULATIONPARAMETERS_H_

#include "WinDllMacros.h"

#include <cstddef>

//! @class SimulationOptions
//! @ingroup simulation
//! @brief Collect the different options for simulation
//! @ref SimulationOptions

class BA_CORE_API_ SimulationOptions
{
public:
    SimulationOptions();
    bool m_mc_integration;
    size_t m_mc_points;
};

inline SimulationOptions::SimulationOptions()
    : m_mc_integration(false)
    , m_mc_points(1)
{
}

#endif /* SIMULATIONPARAMETERS_H_ */

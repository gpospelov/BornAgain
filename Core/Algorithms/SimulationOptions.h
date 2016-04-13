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

#ifndef SIMULATIONOPTIONS_H
#define SIMULATIONOPTIONS_H

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

    bool isIntegrate() const;
    size_t getMcPoints() const;

    //! @brief Enables/disables MonetCarlo integration
    //! @param flag If true, MonteCarlo integration will be used, otherwise analytical calculations
    //! @param mc_points Number of points for MonteCarlo integrator
    void setMonteCarloIntegration(bool flag = true, size_t mc_points=50);

private:
    bool m_mc_integration;
    size_t m_mc_points;
};

inline SimulationOptions::SimulationOptions()
    : m_mc_integration(false)
    , m_mc_points(1)
{
}

inline bool SimulationOptions::isIntegrate() const
{
    return m_mc_integration && m_mc_points>1;
}

inline size_t SimulationOptions::getMcPoints() const
{
    return m_mc_points;
}

inline void SimulationOptions::setMonteCarloIntegration(bool flag, size_t mc_points)
{
    m_mc_integration = flag;
    m_mc_points = mc_points;
}

#endif /* SIMULATIONPARAMETERS_H_ */

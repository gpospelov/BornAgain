// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      StandardSamples/SimulationRegistry.h
//! @brief     Declares class SimulationRegistry.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SIMULATIONREGISTRY_H
#define SIMULATIONREGISTRY_H

#include "IFactory.h"
#include "GISASSimulation.h"

//! @class SimulationRegistry
//! @ingroup standard_samples
//! @brief Registry to create standard pre-defined simulations.
//! Used in functional tests, performance measurements, etc.

class BA_CORE_API_ SimulationRegistry : public IFactory<GISASSimulation>
{
public:
    SimulationRegistry();
};

#endif // SIMULATIONREGISTRY_H

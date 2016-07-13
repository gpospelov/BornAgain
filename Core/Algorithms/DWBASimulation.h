// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Algorithms/DWBASimulation.h
//! @brief     Declares class DWBASimulation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef DWBASIMULATION_H
#define DWBASIMULATION_H

#include "Complex.h"
#include "ISimulation.h"
#include "GISASSimulation.h"
#include "OutputData.h"
#include "ThreadInfo.h"
#include "EigenCore.h"
#include "ProgressHandlerDWBA.h"
#include "SimulationElement.h"

//! @class DWBASimulation
//! @ingroup algorithms_internal
//! @brief Base class for different simulations, using DWBA.

class BA_CORE_API_ DWBASimulation : public ISimulation
{
public:
    DWBASimulation();

    virtual ~DWBASimulation();

    //! Initializes the simulation with the parameters from simulation
    virtual void init(const Simulation &simulation,
                      std::vector<SimulationElement>::iterator begin_it,
                      std::vector<SimulationElement>::iterator end_it);

    //! Returns output data containing calculated intensity.
    const OutputData<double>& getDWBAIntensity() const { return m_dwba_intensity; }

    virtual DWBASimulation* clone() const;

protected:
    //! Returns true if the sample requires a polarized calculation
    bool checkPolarizationPresent() const;

    //! Iterators that defines the sequence of elements that this simulation will work on
    std::vector<SimulationElement>::iterator m_begin_it, m_end_it;

    mutable OutputData<double> m_dwba_intensity;
    SimulationOptions m_sim_options;
    Simulation* mp_simulation;

    ProgressHandlerDWBA m_progress;
};

#endif // DWBASIMULATION_H

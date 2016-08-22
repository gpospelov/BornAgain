// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/DWBASimulation.h
//! @brief     Defines class DWBASimulation.
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

#include "ICloneable.h"
#include "ComputationOutcome.h"
#include "OutputData.h"
#include "ProgressHandlerDWBA.h"
#include "Simulation.h"
#include "SimulationOptions.h"
#include <vector>

class SimulationElement;

//! Base class for DWBA computation MultiLayerDWBASimulation, and for sub-computations
//! MultiLayerRoughnessDWBASimulation and DecoratedLayerDWBASimulation (via LayerDWBASimulation).
//! Controlled by class Simulation.
//! @ingroup algorithms_internal

class BA_CORE_API_ DWBASimulation : public ICloneable
{
public:
    DWBASimulation();
    virtual ~DWBASimulation();
    virtual DWBASimulation* clone() const;

    virtual void run() {}

    //! Initializes the simulation with the parameters from simulation
    virtual void init(
        const SimulationOptions& options,
        const Simulation& simulation,
        std::vector<SimulationElement>::iterator begin_it,
        std::vector<SimulationElement>::iterator end_it);

    //! Returns output data containing calculated intensity.
    const OutputData<double>& getDWBAIntensity() const { return m_dwba_intensity; }

    bool isCompleted() const { return m_outcome.isCompleted(); }
    std::string getRunMessage() const { return m_outcome.getRunMessage(); }

protected:
    virtual void runProtected() {}

    //! Returns true if the sample requires a polarized calculation
    bool checkPolarizationPresent() const;

    //! Iterators that defines the sequence of elements that this simulation will work on
    std::vector<SimulationElement>::iterator m_begin_it, m_end_it;

    mutable OutputData<double> m_dwba_intensity;
    SimulationOptions m_sim_options;
    Simulation* mp_simulation;

    ComputationOutcome m_outcome;
    ProgressHandlerDWBA m_progress;
};

#endif // DWBASIMULATION_H

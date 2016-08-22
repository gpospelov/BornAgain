// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/Computation.h
//! @brief     Defines class Computation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef COMPUTATION_H
#define COMPUTATION_H

#include "ICloneable.h"
#include "ComputationOutcome.h"
#include "ProgressHandlerDWBA.h"
#include "Simulation.h"
#include "SimulationOptions.h"
#include <vector>

class SimulationElement;

//! Base class for DWBA computation MultiLayerComputation, and for sub-computations
//! MultiLayerRoughnessComputation and DecoratedLayerComputation (via LayerComputation).
//! Controlled by class Simulation.
//! @ingroup algorithms_internal

class BA_CORE_API_ Computation : public ICloneable
{
public:
    Computation();
    virtual ~Computation();
    virtual Computation* clone() const;

    virtual void run() {}

    //! Initializes the simulation with the parameters from simulation
    virtual void init(
        const SimulationOptions& options,
        const Simulation& simulation,
        std::vector<SimulationElement>::iterator begin_it,
        std::vector<SimulationElement>::iterator end_it);

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

#endif // COMPUTATION_H

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/IComputation.h
//! @brief     Defines class IComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef ICOMPUTATION_H
#define ICOMPUTATION_H

#include "INoncopyable.h"
#include "ProgressHandlerDWBA.h"
#include "SimulationOptions.h"
#include <vector>

class Simulation;
class SimulationElement;

//! Base class for DWBA computation MainComputation, and for sub-computations
//! RoughMultiLayerComputation and DecoratedLayerComputation (via LayerComputation).
//! Controlled by class Simulation.
//! @ingroup algorithms_internal

class BA_CORE_API_ IComputation : public INoncopyable
{
public:
    IComputation();
    virtual ~IComputation();

    virtual void run() {}

    //! Initializes the simulation with the parameters from simulation
    virtual void init(
        const SimulationOptions& options,
        const Simulation& simulation,
        std::vector<SimulationElement>::iterator begin_it,
        std::vector<SimulationElement>::iterator end_it);

protected:
    virtual void runProtected() {}

    //! Returns true if the sample requires a polarized calculation
    bool checkPolarizationPresent() const;

    //! Iterators that defines the sequence of elements that this simulation will work on
    std::vector<SimulationElement>::iterator m_begin_it, m_end_it;

    SimulationOptions m_sim_options;
    Simulation* mp_simulation;

    ProgressHandlerDWBA m_progress;
};

#endif // ICOMPUTATION_H

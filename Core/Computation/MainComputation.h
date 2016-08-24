// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/MainComputation.h
//! @brief     Defines class MainComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef MULTILAYERCOMPUTATION_H
#define MULTILAYERCOMPUTATION_H

#include "ComputationOutcome.h"
#include "Complex.h"
#include "INoncopyable.h"
#include "ProgressHandlerDWBA.h"
#include "SimulationOptions.h"
#include <vector>

class DecoratedLayerComputation;
class MultiLayer;
class RoughMultiLayerComputation;
class Simulation;
class SimulationElement;

//! Performs a DWBA calculation with given sample and simulation parameters
//! @ingroup algorithms_internal

class BA_CORE_API_ MainComputation : public INoncopyable
{
public:
    MainComputation(
        const MultiLayer* p_multi_layer,
        const SimulationOptions& options,
        Simulation& simulation,
        const std::vector<SimulationElement>::iterator& begin_it,
        const std::vector<SimulationElement>::iterator& end_it);
    ~MainComputation();

    void run();

    bool isCompleted() const { return m_outcome.isCompleted(); }
    std::string getRunMessage() const { return m_outcome.getRunMessage(); }

private:
    void runProtected();

    //! calculates intensity map for samples with magnetization
    void collectRTCoefficientsScalar();
    void collectRTCoefficientsMatrix();

    //! Iterators that defines the sequence of elements that this simulation will work on
    std::vector<SimulationElement>::iterator m_begin_it, m_end_it;

    SimulationOptions m_sim_options;

    ProgressHandlerDWBA m_progress;

    std::vector<std::vector<DecoratedLayerComputation*>> m_layer_computation;
    MultiLayer* mp_multi_layer;
    RoughMultiLayerComputation* mp_roughness_computation;
    ComputationOutcome m_outcome;
};

#endif // MULTILAYERCOMPUTATION_H

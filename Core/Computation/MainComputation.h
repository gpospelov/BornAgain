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

#ifndef MAINCOMPUTATION_H
#define MAINCOMPUTATION_H

#include "ComputationStatus.h"
#include "Complex.h"
#include "INoncopyable.h"
#include "SafePointerVector.h"
#include "SimulationOptions.h"
#include <memory>
#include <vector>

class ILayerSpecularInfo;
class MultiLayer;
class IComputationTerm;
class ProgressHandler;
class SimulationElement;

//! Performs a single-threaded DWBA computation with given sample and simulation parameters,
//! for a given span of detector bins.
//!
//! Controlled by the multi-threading machinery in Simulation::runSingleSimulation().
//!
//! @ingroup algorithms_internal

class MainComputation final : public INoncopyable
{
public:
    MainComputation(
        const MultiLayer& p_multi_layer,
        const SimulationOptions& options,
        ProgressHandler& progress,
        const std::vector<SimulationElement>::iterator& begin_it,
        const std::vector<SimulationElement>::iterator& end_it);
    ~MainComputation();

    void run();

    bool isCompleted() const { return m_status.isCompleted(); }
    std::string errorMessage() const { return m_status.errorMessage(); }

private:
    void runProtected();
    void collectRTCoefficientsScalar();
    void collectRTCoefficientsMatrix();
    void passFresnelInfo();

    std::unique_ptr<MultiLayer> mP_multi_layer;
    std::unique_ptr<MultiLayer> mP_inverted_multilayer;
    SimulationOptions m_sim_options;
    ProgressHandler* m_progress;
    //! these iterators define the span of detector bins this simulation will work on
    std::vector<SimulationElement>::iterator m_begin_it, m_end_it;

    std::vector<IComputationTerm*> m_computation_terms;

    //! contains the information, necessary to calculate the Fresnel coefficients
    SafePointerVector<ILayerSpecularInfo> m_fresnel_info;

    ComputationStatus m_status;
};

#endif // MAINCOMPUTATION_H

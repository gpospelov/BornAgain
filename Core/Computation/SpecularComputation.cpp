// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/SpecularComputation.cpp
//! @brief     Implements class SpecularComputation.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SpecularComputation.h"
#include "IComputationUtils.h"
#include "MultiLayer.h"
#include "ProgressHandler.h"
#include "SpecularSimulationElement_.h"

static_assert(std::is_copy_constructible<SpecularComputation>::value == false,
              "SpecularComputation should not be copy constructible");
static_assert(std::is_copy_assignable<SpecularComputation>::value == false,
              "SpecularComputation should not be copy assignable");

SpecularComputation::SpecularComputation(const MultiLayer& multilayer,
                                         const SimulationOptions& options,
                                         ProgressHandler& progress, SpecularElementIter begin_it,
                                         SpecularElementIter end_it)
    : IComputation(options, progress, multilayer)
    , m_begin_it(begin_it), m_end_it(end_it)
{}

SpecularComputation::~SpecularComputation() = default;

void SpecularComputation::runProtected()
{
    if (!mp_progress->alive() || mP_multi_layer->requiresMatrixRTCoefficients())
        return;

    m_computation_term.setProgressHandler(mp_progress);
    const std::unique_ptr<MultiLayer> avr_sample =
        IComputationUtils::CreateAveragedMultilayer(*mP_multi_layer, m_sim_options);
    for (auto it = m_begin_it; it != m_end_it; ++it)
        m_computation_term.compute(*it, *avr_sample);
}

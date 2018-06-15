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
#include "Layer.h"
#include "MatrixFresnelMap.h"
#include "MultiLayer.h"
#include "ProgressHandler.h"
#include "ScalarFresnelMap.h"
#include "SpecularComputationTerm.h"

static_assert(std::is_copy_constructible<SpecularComputation>::value == false,
              "SpecularComputation should not be copy constructible");
static_assert(std::is_copy_assignable<SpecularComputation>::value == false,
              "SpecularComputation should not be copy assignable");

SpecularComputation::SpecularComputation(const MultiLayer& multilayer,
                                         const SimulationOptions& options,
                                         ProgressHandler& progress,
                                         SpecularElementIter begin_it,
                                         SpecularElementIter end_it)
    : IComputation(options, progress, multilayer)
    , m_begin_it(begin_it)
    , m_end_it(end_it)
    , mP_fresnel_map(IComputationUtils::CreateFresnelMap(multilayer, options, false))
    , m_computation_term(mP_multi_layer.get(), mP_fresnel_map.get())
{
}

SpecularComputation::~SpecularComputation() = default;

void SpecularComputation::runProtected()
{
    if (!m_progress->alive())
        return;
    m_computation_term.eval(m_progress, m_begin_it, m_end_it);
}

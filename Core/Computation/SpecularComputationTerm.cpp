// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/SpecularComputationTerm.cpp
//! @brief     Implements functor SpecularComputationTerm.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "SpecularComputationTerm.h"
#include "DelayedProgressCounter.h"
#include "ScalarRTCoefficients.h"
#include "SpecularMatrix.h"
#include "SpecularSimulationElement.h"

SpecularComputationTerm::SpecularComputationTerm() {}

SpecularComputationTerm::~SpecularComputationTerm() = default;

void SpecularComputationTerm::setProgressHandler(ProgressHandler* p_progress)
{
    mP_progress_counter.reset(new DelayedProgressCounter(p_progress, 100));
}

void SpecularComputationTerm::compute(SpecularSimulationElement& elem,
                                      const std::vector<Slice>& slices) const
{
    if (!elem.isCalculated())
        return;

    auto coeff = SpecularMatrix::Execute(slices, elem.produceKz(slices));
    elem.setIntensity(std::norm(coeff[0].getScalarR()));

    if (mP_progress_counter)
        mP_progress_counter->stepProgress();
}

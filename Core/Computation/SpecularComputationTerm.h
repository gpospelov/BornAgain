// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Computation/SpecularComputationTerm.h
//! @brief     Defines functor SpecularComputationTerm.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SPECULARCOMPUTATIONTERM_H_
#define SPECULARCOMPUTATIONTERM_H_

#include <memory>

class DelayedProgressCounter;
class MultiLayer;
class ProgressHandler;
class SpecularSimulationElement;

//! Computes the specular scattering.
//! Used by SpecularComputation.
//! @ingroup algorithms_internal

class SpecularComputationTerm
{
public:
    SpecularComputationTerm();
    ~SpecularComputationTerm();

    void setProgressHandler(ProgressHandler* p_progress);
    void compute(SpecularSimulationElement& elem, const MultiLayer& sample) const;

private:
    std::unique_ptr<DelayedProgressCounter> mP_progress_counter;
};

#endif /* SPECULARCOMPUTATIONTERM_H_ */

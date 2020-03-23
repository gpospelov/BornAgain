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

#include "ISpecularStrategy.h"

#include <memory>
#include <vector>

class DelayedProgressCounter;
class MatrixRTCoefficients_v2;
class ProgressHandler;
class SpecularSimulationElement;
class Slice;

//! Computes the specular scattering.
//! Used by SpecularComputation.
//! @ingroup algorithms_internal

class SpecularComputationTerm
{
public:
    SpecularComputationTerm(std::unique_ptr<ISpecularStrategy> strategy);
    virtual ~SpecularComputationTerm();

    void setProgressHandler(ProgressHandler* p_progress);
    void compute(SpecularSimulationElement& elem, const std::vector<Slice>& slices) const;

protected:
    virtual void eval(SpecularSimulationElement& elem, const std::vector<Slice>& slices) const = 0;

    std::unique_ptr<ISpecularStrategy> m_Strategy;
private:
    std::unique_ptr<DelayedProgressCounter> mP_progress_counter;
};

class SpecularScalarTerm : public SpecularComputationTerm
{
public:
    SpecularScalarTerm(std::unique_ptr<ISpecularStrategy> strategy);
private:
    ~SpecularScalarTerm() override;
protected:
    void eval(SpecularSimulationElement& elem, const std::vector<Slice>& slices) const override;
};

class SpecularMatrixTerm : public SpecularComputationTerm
{
public:
    SpecularMatrixTerm(std::unique_ptr<ISpecularStrategy> strategy);
private:
    ~SpecularMatrixTerm() override;
protected:
    void eval(SpecularSimulationElement& elem, const std::vector<Slice>& slices) const override;
    double intensity(const SpecularSimulationElement& elem,
                     ISpecularStrategy::single_coeff_t& coeff) const;
};

#endif /* SPECULARCOMPUTATIONTERM_H_ */

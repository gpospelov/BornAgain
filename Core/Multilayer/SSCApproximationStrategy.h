// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SSCApproximationStrategy.h
//! @brief     Defines class SSCApproximationStrategy.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SSCAPPROXIMATIONSTRATEGY_H
#define SSCAPPROXIMATIONSTRATEGY_H

#include "IInterferenceFunctionStrategy.h"
#include "SSCAHelper.h"

class SimulationElement;

//! Strategy class to compute the total scattering from a particle layout
//! in the size-spacing correlation approximation.
//! @ingroup algorithms_internal

class SSCApproximationStrategy final : public IInterferenceFunctionStrategy
{
public:
    SSCApproximationStrategy(SimulationOptions sim_params, double kappa, bool polarized);

protected:
    void strategy_specific_post_init() override;
    double evaluateForList(const SimulationElement& sim_element) const override;

private:
    double scalarCalculation(const SimulationElement& sim_element) const;
    double polarizedCalculation(const SimulationElement& sim_element) const;
    complex_t getMeanFormfactorNorm(double qp, const std::vector<complex_t>& precomputed_ff) const;
    void getMeanFormfactors(double qp, Eigen::Matrix2cd& ff_orig, Eigen::Matrix2cd& ff_conj,
                            const matrixFFVector_t& precomputed_ff) const;
    SSCAHelper m_helper;
    bool m_polarized;
};

#endif // SSCAPPROXIMATIONSTRATEGY_H

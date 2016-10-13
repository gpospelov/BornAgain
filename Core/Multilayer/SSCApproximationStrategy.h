// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Multilayer/SSCApproximationStrategy.h
//! @brief     Defines classes SSCApproximationStrategy,
//!              SSCApproximationStrategy1, SSCApproximationStrategy2.
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

class SimulationElement;

//! Virtual base class for SSCApproximationStrategy1 and SSCApproximationStrategy2,
//! which compute the total scalar/polarized scattering from a decorated layer
//! in size-spacing correlation approximation.
//! @ingroup algorithms_internal

class SSCApproximationStrategy : public virtual IInterferenceFunctionStrategy
{
public:
    SSCApproximationStrategy(double kappa);

protected:
    complex_t calculatePositionOffsetPhase(double qp, double kappa, size_t index) const;
    complex_t getCharacteristicDistribution(double qp) const;
    complex_t getCharacteristicSizeCoupling(double qp, double kappa) const;

    double m_mean_radius;
    double m_kappa;

private:
    void strategy_specific_post_init() final;

    void initMeanRadius();
};

//! Strategy class to compute the total scalar scattering from a decorated layer
//! in size-spacing correlation approximation.

class SSCApproximationStrategy1
    : public IInterferenceFunctionStrategy1
    , public SSCApproximationStrategy
{
public:
    SSCApproximationStrategy1(SimulationOptions sim_params, double kappa)
        : IInterferenceFunctionStrategy(sim_params), SSCApproximationStrategy(kappa) {}

private:
    double evaluateForList(const SimulationElement& sim_element) const final;

    complex_t getMeanCharacteristicFF(double qp) const;
    complex_t getMeanConjCharacteristicFF(double qp) const;
};

//! Strategy class to compute the total polarized scattering from a decorated layer
//! in size-spacing correlation approximation.

class SSCApproximationStrategy2
    : public IInterferenceFunctionStrategy2
    , public SSCApproximationStrategy
{
public:
    SSCApproximationStrategy2(SimulationOptions sim_params, double kappa)
        : IInterferenceFunctionStrategy(sim_params), SSCApproximationStrategy(kappa) {}

private:
    double evaluateForList(const SimulationElement& sim_element) const final;

    Eigen::Matrix2cd getMeanCharacteristicFF(double qp) const;
    Eigen::Matrix2cd getMeanConjCharacteristicFF(double qp) const;

};

#endif // SSCAPPROXIMATIONSTRATEGY_H

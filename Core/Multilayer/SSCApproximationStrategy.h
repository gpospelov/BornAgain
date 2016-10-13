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

class SimulationElement;

//! Strategy which implements size spacing correlation approximation.
//! @ingroup algorithms_internal

class SSCApproximationStrategy : public virtual IInterferenceFunctionStrategy
{
public:
    SSCApproximationStrategy(double kappa);
    virtual ~SSCApproximationStrategy() {}

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

//!

class SSCApproximationStrategy1
    : public IInterferenceFunctionStrategy1
    , public SSCApproximationStrategy
{
public:
    SSCApproximationStrategy1(SimulationOptions sim_params, double kappa)
        : IInterferenceFunctionStrategy(sim_params), SSCApproximationStrategy(kappa) {}
    ~SSCApproximationStrategy1() final {}

private:
    double evaluateForList(const SimulationElement& sim_element) const final;

    complex_t getMeanCharacteristicFF(double qp) const;
    complex_t getMeanConjCharacteristicFF(double qp) const;
};

//!

class SSCApproximationStrategy2
    : public IInterferenceFunctionStrategy2
    , public SSCApproximationStrategy
{
public:
    SSCApproximationStrategy2(SimulationOptions sim_params, double kappa)
        : IInterferenceFunctionStrategy(sim_params), SSCApproximationStrategy(kappa) {}
    ~SSCApproximationStrategy2() final {}

private:
    double evaluateForList(const SimulationElement& sim_element) const final;

    Eigen::Matrix2cd getMeanCharacteristicFF(double qp) const;
    Eigen::Matrix2cd getMeanConjCharacteristicFF(double qp) const;

};

#endif // SSCAPPROXIMATIONSTRATEGY_H

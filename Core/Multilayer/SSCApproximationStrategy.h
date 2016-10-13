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

class SSCApproximationStrategy : public IInterferenceFunctionStrategy
{
public:
    SSCApproximationStrategy(SimulationOptions sim_params, double kappa);
    ~SSCApproximationStrategy() final {}

private:
    void strategy_specific_post_init() final;
    double evaluateForList(const SimulationElement& sim_element) const final;
    double evaluateForMatrixList(const SimulationElement& sim_element) const final;

    complex_t getMeanCharacteristicFF(double qp) const;
    complex_t getMeanConjCharacteristicFF(double qp) const;
    Eigen::Matrix2cd getMeanCharacteristicMatrixFF(double qp) const;
    Eigen::Matrix2cd getMeanConjCharacteristicMatrixFF(double qp) const;

    complex_t getCharacteristicDistribution(double qp) const;
    complex_t getCharacteristicSizeCoupling(double qp, double kappa) const;
    complex_t calculatePositionOffsetPhase(double qp, double kappa, size_t index) const;
    void initMeanRadius();

    double m_mean_radius;
    double m_kappa;
};

#endif // SSCAPPROXIMATIONSTRATEGY_H

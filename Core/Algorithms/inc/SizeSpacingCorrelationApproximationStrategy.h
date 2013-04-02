// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Algorithms/inc/SizeSpacingCorrelationApproximationStrategy.h
//! @brief     Defines class SizeSpacingCorrelationApproximationStrategy.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SIZESPACINGCORRELATIONAPPROXIMATIONSTRATEGY_H_
#define SIZESPACINGCORRELATIONAPPROXIMATIONSTRATEGY_H_

#include "Types.h"
#include "IInterferenceFunctionStrategy.h"

//! ?

class SizeSpacingCorrelationApproximationStrategy : public IInterferenceFunctionStrategy
{
 public:
    SizeSpacingCorrelationApproximationStrategy(SimulationParameters sim_params, double kappa);
    virtual ~SizeSpacingCorrelationApproximationStrategy() {}

    virtual void init(const SafePointerVector<FormFactorInfo>& form_factor_infos,
            const SafePointerVector<IInterferenceFunction>& ifs);
    virtual double evaluate(const cvector_t& k_i, const Bin1DCVector& k_f_bin,
            double alpha_i, double alpha_f) const;
 private:
    bool checkVectorSizes() const;
    complex_t getMeanCharacteristicFF(const cvector_t& k_i, const Bin1DCVector& k_f_bin,
            double alpha_i, double alpha_f) const;
    complex_t getMeanConjCharacteristicFF(const cvector_t& k_i, const Bin1DCVector& k_f_bin,
            double alpha_i, double alpha_f) const;
    complex_t getCharacteristicDistribution(double qp) const;
    complex_t getCharacteristicSizeCoupling(double qp, double kappa) const;
    complex_t calculatePositionOffsetPhase(double qp, double kappa, size_t index) const;
    double getqp(const cvector_t& k_i, const Bin1DCVector& k_f_bin) const;
    void initMeanRadius();
    double m_mean_radius;
    double m_kappa;
};

#endif /* SIZESPACINGCORRELATIONAPPROXIMATIONSTRATEGY_H_ */



#ifndef SIZESPACINGCORRELATIONAPPROXIMATIONSTRATEGY_H_
#define SIZESPACINGCORRELATIONAPPROXIMATIONSTRATEGY_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   SizeSpacingCorrelationApproximationStrategy.h
//! @brief  Definition of SizeSpacingCorrelationApproximationStrategy class
//! @author Scientific Computing Group at FRM II
//! @date   Jan 17, 2013

#include "Types.h"
#include "IInterferenceFunctionStrategy.h"

class SizeSpacingCorrelationApproximationStrategy : public IInterferenceFunctionStrategy
{
public:
    SizeSpacingCorrelationApproximationStrategy(SimulationParameters sim_params, double kappa);
    virtual ~SizeSpacingCorrelationApproximationStrategy() {}

    virtual void init(const SafePointerVector<FormFactorInfo> &form_factor_infos,
            const SafePointerVector<IInterferenceFunction> &ifs);
    virtual double evaluate(const cvector_t &k_i, const Bin1DCVector &k_f_bin,
            double alpha_i, double alpha_f) const;
private:
    bool checkVectorSizes() const;
    complex_t getMeanCharacteristicFF(const cvector_t &k_i, const Bin1DCVector &k_f_bin,
            double alpha_i, double alpha_f) const;
    complex_t getMeanConjCharacteristicFF(const cvector_t &k_i, const Bin1DCVector &k_f_bin,
            double alpha_i, double alpha_f) const;
    complex_t getCharacteristicDistribution(double qp) const;
    complex_t getCharacteristicSizeCoupling(double qp, double kappa) const;
    complex_t calculatePositionOffsetPhase(double qp, double kappa, size_t index) const;
    double getqp(const cvector_t &k_i, const Bin1DCVector &k_f_bin) const;
    void initMeanRadius();
    double m_mean_radius;
    double m_kappa;
};


#endif /* SIZESPACINGCORRELATIONAPPROXIMATIONSTRATEGY_H_ */

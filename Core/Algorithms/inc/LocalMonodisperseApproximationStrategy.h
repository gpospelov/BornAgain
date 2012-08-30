#ifndef LOCALMONODISPERSEAPPROXIMATIONSTRATEGY_H_
#define LOCALMONODISPERSEAPPROXIMATIONSTRATEGY_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   LocalMonodisperseApproximationStrategy.h
//! @brief  Definition of LocalMonodisperseApproximationStrategy class
//! @author Scientific Computing Group at FRM II
//! @date   Jun 29, 2012

#include "IInterferenceFunctionStrategy.h"

class LocalMonodisperseApproximationStrategy : public IInterferenceFunctionStrategy
{
public:
    LocalMonodisperseApproximationStrategy();
    virtual ~LocalMonodisperseApproximationStrategy() {}

    virtual void init(const std::vector<IFormFactor *> &form_factors,
            const std::vector<double> &fractions,
            const std::vector<IInterferenceFunction *> &interference_functions);
    virtual double evaluate(cvector_t k_i, cvector_t k_f,
            double alpha_i, double alpha_f) const;
private:
    bool checkVectorSizes();
};



#endif /* LOCALMONODISPERSEAPPROXIMATIONSTRATEGY_H_ */

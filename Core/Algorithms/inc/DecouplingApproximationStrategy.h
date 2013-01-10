#ifndef DECOUPLINGAPPROXIMATIONSTRATEGY_H_
#define DECOUPLINGAPPROXIMATIONSTRATEGY_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   DecouplingApproximationStrategy.h
//! @brief  Definition of DecouplingApproximationStrategy class
//! @author Scientific Computing Group at FRM II
//! @date   Jun 29, 2012

#include "Types.h"
#include "IInterferenceFunctionStrategy.h"

class DecouplingApproximationStrategy : public IInterferenceFunctionStrategy
{
public:
    DecouplingApproximationStrategy();
    virtual ~DecouplingApproximationStrategy() {}

    virtual void init(const std::vector<IFormFactor *> &form_factors,
            const std::vector<double> &fractions,
            const std::vector<IInterferenceFunction *> &interference_functions);
    virtual double evaluate(const cvector_t &k_i, const Bin1DCVector &k_f_bin,
            double alpha_i, double alpha_f) const;
private:
    bool checkVectorSizes() const;
};


#endif /* DECOUPLINGAPPROXIMATIONSTRATEGY_H_ */

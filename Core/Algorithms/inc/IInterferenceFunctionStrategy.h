#ifndef IINTERFERENCEFUNCTIONSTRATEGY_H_
#define IINTERFERENCEFUNCTIONSTRATEGY_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   IInterferenceFunctionStrategy.h
//! @brief  Definition of IInterferenceFunctionStrategy class
//! @author Scientific Computing Group at FRM II
//! @date   Jun 29, 2012

#include "Types.h"
#include "IFormFactor.h"
#include "IInterferenceFunction.h"
#include "Bin.h"
#include "SafePointerVector.h"
#include "StrategyBuilder.h"

#include <vector>

class IInterferenceFunctionStrategy
{
public:
    virtual ~IInterferenceFunctionStrategy() {};
    virtual void init(const SafePointerVector<FormFactorInfo> &form_factor_infos,
            const SafePointerVector<IInterferenceFunction> &ifs);
    virtual double evaluate(const cvector_t &k_i, const Bin1DCVector &k_f_bin,
            double alpha_i, double alpha_f) const=0;
protected:
    SafePointerVector<FormFactorInfo> m_ff_infos; //!< Form factor info
    SafePointerVector<IInterferenceFunction> m_ifs; //!< Interference functions
};

inline void IInterferenceFunctionStrategy::init(
        const SafePointerVector<FormFactorInfo> &form_factor_infos,
        const SafePointerVector<IInterferenceFunction> &ifs)
{
    m_ff_infos = form_factor_infos;
    m_ifs = ifs;
}

#endif /* IINTERFERENCEFUNCTIONSTRATEGY_H_ */

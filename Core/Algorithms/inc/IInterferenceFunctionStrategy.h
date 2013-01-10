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

#include <vector>

class IInterferenceFunctionStrategy
{
public:
    virtual ~IInterferenceFunctionStrategy();
    virtual void init(const std::vector<IFormFactor *> &form_factors,
            const std::vector<double> &fractions,
            const std::vector<IInterferenceFunction *> &interference_functions);
    virtual double evaluate(const cvector_t &k_i, const Bin1DCVector &k_f_bin,
            double alpha_i, double alpha_f) const=0;
protected:
    void deleteVectors();
    SafePointerVector<IFormFactor> m_form_factors; //!< Includes Scattering Length Density
    std::vector<double> m_fractions;
    SafePointerVector<IInterferenceFunction> m_interference_functions;
};

inline IInterferenceFunctionStrategy::~IInterferenceFunctionStrategy()
{
}

inline void IInterferenceFunctionStrategy::init(
        const std::vector<IFormFactor*>& form_factors,
        const std::vector<double>& fractions,
        const std::vector<IInterferenceFunction*>& interference_functions)
{
    m_fractions = fractions;
    m_form_factors.clear();
    for (size_t i=0; i<form_factors.size(); ++i) {
        m_form_factors.push_back(form_factors[i]->clone());
    }
    m_interference_functions.clear();
    for (size_t i=0; i<interference_functions.size(); ++i) {
        m_interference_functions.push_back(interference_functions[i]->clone());
    }
}

#endif /* IINTERFERENCEFUNCTIONSTRATEGY_H_ */

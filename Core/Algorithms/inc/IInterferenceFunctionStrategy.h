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

#include <vector>

class IInterferenceFunctionStrategy
{
public:
    virtual ~IInterferenceFunctionStrategy();
    virtual void init(const std::vector<IFormFactor *> &form_factors,
            const std::vector<double> &fractions,
            const std::vector<IInterferenceFunction *> &interference_functions);
    virtual double evaluate(cvector_t k_i, cvector_t k_f,
            double alpha_i, double alpha_f) const=0;
//    virtual double evaluateForComplexkz(kvector_t k_i, kvector_t k_f,
//            complex_t k_iz, complex_t k_fz) const=0;
protected:
    void deleteVectors();
    std::vector<IFormFactor*> m_form_factors; //!< Includes Scattering Length Density
    std::vector<double> m_fractions;
    std::vector<IInterferenceFunction*> m_interference_functions;
};

inline IInterferenceFunctionStrategy::~IInterferenceFunctionStrategy()
{
    deleteVectors();
}

inline void IInterferenceFunctionStrategy::init(
        const std::vector<IFormFactor*>& form_factors,
        const std::vector<double>& fractions,
        const std::vector<IInterferenceFunction*>& interference_functions)
{
    deleteVectors();
    m_fractions = fractions;
    for (size_t i=0; i<form_factors.size(); ++i) {
        m_form_factors.push_back(form_factors[i]->clone());
    }
    for (size_t i=0; i<interference_functions.size(); ++i) {
        m_interference_functions.push_back(interference_functions[i]->clone());
    }
}

inline void IInterferenceFunctionStrategy::deleteVectors()
{
    for (size_t i=0; i<m_form_factors.size(); ++i) {
        delete m_form_factors[i];
    }
    for (size_t i=0; i<m_interference_functions.size(); ++i) {
        delete m_interference_functions[i];
    }
    m_form_factors.clear();
    m_interference_functions.clear();
}



#endif /* IINTERFERENCEFUNCTIONSTRATEGY_H_ */

#ifndef FORMFACTORDECORATORFACTOR_H_
#define FORMFACTORDECORATORFACTOR_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FormFactorDecoratorFactor.h
//! @brief  Definition of FormFactorDecoratorFactor class
//! @author Scientific Computing Group at FRM II
//! @date   Jun 29, 2012

#include "IFormFactor.h"


class FormFactorDecoratorFactor : public IFormFactorDecorator
{
public:
    FormFactorDecoratorFactor(IFormFactor *p_form_factor, complex_t factor);
    virtual FormFactorDecoratorFactor *clone() const;
    virtual ~FormFactorDecoratorFactor();

    virtual complex_t evaluate(kvector_t k_i, kvector_t k_f) const;
    virtual complex_t evaluate(cvector_t k_i, cvector_t k_f) const;
    virtual complex_t evaluateForComplexkz(kvector_t k_i, kvector_t k_f, complex_t k_iz, complex_t k_fz) const;
    virtual int getNumberOfStochasticParameters() const;

protected:
    complex_t m_factor;
};

inline FormFactorDecoratorFactor::FormFactorDecoratorFactor(
        IFormFactor* p_form_factor, complex_t factor)
: IFormFactorDecorator(p_form_factor)
, m_factor(factor)
{
}

inline FormFactorDecoratorFactor* FormFactorDecoratorFactor::clone() const
{
    return new FormFactorDecoratorFactor(mp_form_factor->clone(), m_factor);
}

inline FormFactorDecoratorFactor::~FormFactorDecoratorFactor()
{
    delete mp_form_factor;
}

inline complex_t FormFactorDecoratorFactor::evaluate(kvector_t k_i,
        kvector_t k_f) const
{
    return m_factor*mp_form_factor->evaluate(k_i, k_f);
}

inline complex_t FormFactorDecoratorFactor::evaluate(cvector_t k_i,
        cvector_t k_f) const
{
    return m_factor*mp_form_factor->evaluate(k_i, k_f);
}

inline complex_t FormFactorDecoratorFactor::evaluateForComplexkz(kvector_t k_i,
        kvector_t k_f, complex_t k_iz, complex_t k_fz) const
{
    return m_factor*mp_form_factor->evaluateForComplexkz(k_i, k_f, k_iz, k_fz);
}

inline int FormFactorDecoratorFactor::getNumberOfStochasticParameters() const
{
    return mp_form_factor->getNumberOfStochasticParameters();
}





#endif /* FORMFACTORDECORATORFACTOR_H_ */

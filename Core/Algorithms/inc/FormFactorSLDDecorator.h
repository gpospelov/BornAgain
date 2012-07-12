#ifndef FORMFACTORSLDDECORATOR_H_
#define FORMFACTORSLDDECORATOR_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FormFactorSLDDecorator.h
//! @brief  Definition of FormFactorSLDDecorator class
//! @author Scientific Computing Group at FRM II
//! @date   Jun 29, 2012

#include "IFormFactor.h"


class FormFactorSLDDecorator : public IFormFactor
{
public:
    FormFactorSLDDecorator(IFormFactor *p_form_factor, complex_t sld);
    virtual FormFactorSLDDecorator *clone() const;
    virtual ~FormFactorSLDDecorator();

    virtual complex_t evaluate(kvector_t k_i, kvector_t k_f) const;
    virtual complex_t evaluateForComplexkz(kvector_t k_i, kvector_t k_f, complex_t k_iz, complex_t k_fz) const;
    virtual int getNumberOfStochasticParameters() const;

private:
    //! copy constructor and assignment operator are hidden since there is a clone method
    FormFactorSLDDecorator(const FormFactorSLDDecorator &);
    FormFactorSLDDecorator &operator=(const FormFactorSLDDecorator &);

    IFormFactor *mp_form_factor;
    complex_t m_sld;
};

inline FormFactorSLDDecorator::FormFactorSLDDecorator(
        IFormFactor* p_form_factor, complex_t sld)
: mp_form_factor(p_form_factor)
, m_sld(sld)
{
}

inline FormFactorSLDDecorator* FormFactorSLDDecorator::clone() const
{
    return new FormFactorSLDDecorator(mp_form_factor->clone(), m_sld);
}

inline FormFactorSLDDecorator::~FormFactorSLDDecorator()
{
    delete mp_form_factor;
}

inline complex_t FormFactorSLDDecorator::evaluate(kvector_t k_i,
        kvector_t k_f) const
{
    return m_sld*mp_form_factor->evaluate(k_i, k_f);
}

inline complex_t FormFactorSLDDecorator::evaluateForComplexkz(kvector_t k_i,
        kvector_t k_f, complex_t k_iz, complex_t k_fz) const
{
    return m_sld*mp_form_factor->evaluateForComplexkz(k_i, k_f, k_iz, k_fz);
}

inline int FormFactorSLDDecorator::getNumberOfStochasticParameters() const
{
    return mp_form_factor->getNumberOfStochasticParameters();
}





#endif /* FORMFACTORSLDDECORATOR_H_ */

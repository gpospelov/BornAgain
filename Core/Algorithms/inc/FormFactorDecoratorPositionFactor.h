#ifndef FORMFACTORDECORATORPOSITIONFACTOR_H_
#define FORMFACTORDECORATORPOSITIONFACTOR_H_
// ********************************************************************
// * The BornAgain project                                            *
// * Simulation of neutron and x-ray scattering at grazing incidence  *
// *                                                                  *
// * LICENSE AND DISCLAIMER                                           *
// * Lorem ipsum dolor sit amet, consectetur adipiscing elit.  Mauris *
// * eget quam orci. Quisque  porta  varius  dui,  quis  posuere nibh *
// * mollis quis. Mauris commodo rhoncus porttitor.                   *
// ********************************************************************
//! @file   FormFactorDecoratorPositionFactor.h
//! @brief  Definition of
//! @author Scientific Computing Group at FRM II
//! @date   Jul 17, 2012

#include "Types.h"
#include "IFormFactor.h"

#include <cmath>

class FormFactorDecoratorPositionFactor : public IFormFactorDecorator
{
public:
    FormFactorDecoratorPositionFactor(const IFormFactor &form_factor, kvector_t position);
    virtual ~FormFactorDecoratorPositionFactor();
    virtual FormFactorDecoratorPositionFactor *clone() const;

    virtual complex_t evaluate(kvector_t k_i, kvector_t k_f) const;

    virtual complex_t evaluateForComplexkz(kvector_t k_i, kvector_t k_f, complex_t k_iz, complex_t k_fz) const;

    virtual int getNumberOfStochasticParameters() const {
        return mp_form_factor->getNumberOfStochasticParameters();
    }
protected:
    kvector_t m_position;
};

inline FormFactorDecoratorPositionFactor::FormFactorDecoratorPositionFactor(
        const IFormFactor& form_factor, kvector_t position)
: IFormFactorDecorator(form_factor.clone())
, m_position(position)
{
}

inline FormFactorDecoratorPositionFactor::~FormFactorDecoratorPositionFactor()
{
    delete mp_form_factor;
}

inline FormFactorDecoratorPositionFactor* FormFactorDecoratorPositionFactor::clone() const
{
    return new FormFactorDecoratorPositionFactor(*mp_form_factor, m_position);
}

inline complex_t FormFactorDecoratorPositionFactor::evaluate(kvector_t k_i,
        kvector_t k_f) const
{
    kvector_t q = k_i - k_f;
    double qr = q.x()*m_position.x() + q.y()*m_position.y() + q.z()*m_position.z();
    complex_t pos_factor = std::exp(complex_t(0.0, 1.0)*qr);
    return pos_factor*mp_form_factor->evaluate(k_i, k_f);
}

inline complex_t FormFactorDecoratorPositionFactor::evaluateForComplexkz(
        kvector_t k_i, kvector_t k_f, complex_t k_iz, complex_t k_fz) const
{
    kvector_t q = k_i - k_f;
    complex_t qr = q.x()*m_position.x() + q.y()*m_position.y() + (k_iz - k_fz)*m_position.z();
    complex_t pos_factor = std::exp(complex_t(0.0, 1.0)*qr);
    return pos_factor*mp_form_factor->evaluateForComplexkz(k_i, k_f, k_iz, k_fz);
}

#endif /* FORMFACTORDECORATORPOSITIONFACTOR_H_ */

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
#include "Units.h"

class FormFactorDecoratorPositionFactor : public IFormFactorDecorator
{
public:
    FormFactorDecoratorPositionFactor(const IFormFactor &form_factor, kvector_t position);
    virtual ~FormFactorDecoratorPositionFactor() {}
    virtual FormFactorDecoratorPositionFactor *clone() const;

    virtual complex_t evaluate(const cvector_t &k_i, const cvector_t &k_f, double alpha_i, double alpha_f) const;

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

inline FormFactorDecoratorPositionFactor* FormFactorDecoratorPositionFactor::clone() const
{
    return new FormFactorDecoratorPositionFactor(*mp_form_factor, m_position);
}

inline complex_t FormFactorDecoratorPositionFactor::evaluate(const cvector_t &k_i,
        const cvector_t &k_f, double alpha_i, double alpha_f) const
{
    cvector_t q = k_i - k_f;
    complex_t qr = q.x()*m_position.x() + q.y()*m_position.y() + q.z()*m_position.z();
    complex_t pos_factor = std::exp(complex_t(0.0, 1.0)*qr);
    return pos_factor*mp_form_factor->evaluate(k_i, k_f, alpha_i, alpha_f);
}

#endif /* FORMFACTORDECORATORPOSITIONFACTOR_H_ */

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorDecoratorFactor.h
//! @brief     Defines class FormFactorDecoratorFactor.
//!
//! @homepage  http://apps.jcns.fz-juelich.de/BornAgain
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2013
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORDECORATORFACTOR_H_
#define FORMFACTORDECORATORFACTOR_H_

#include "IFormFactorDecorator.h"

//! Decorates a form factor with a constant factor

class BA_CORE_API_ FormFactorDecoratorFactor : public IFormFactorDecorator
{
public:
    FormFactorDecoratorFactor(IFormFactor *p_form_factor, const complex_t& factor);
    virtual FormFactorDecoratorFactor *clone() const;
    virtual ~FormFactorDecoratorFactor() {}

    //! Evaluate the form factor for scalar calculations
    virtual complex_t evaluate(const cvector_t& k_i,
            const Bin1DCVector& k_f_bin, Bin1D alpha_f_bin) const;

    virtual int getNumberOfStochasticParameters() const;

protected:
    complex_t m_factor;
};

inline FormFactorDecoratorFactor::FormFactorDecoratorFactor(
        IFormFactor* p_form_factor, const complex_t& factor)
: IFormFactorDecorator(p_form_factor)
, m_factor(factor)
{
    setName("FormFactorDecoratorFactor");
}

inline FormFactorDecoratorFactor* FormFactorDecoratorFactor::clone() const
{
    FormFactorDecoratorFactor *result = new FormFactorDecoratorFactor(
            mp_form_factor->clone(), m_factor);
    result->setName(getName());
    return result;
}

inline complex_t FormFactorDecoratorFactor::evaluate(const cvector_t& k_i,
        const Bin1DCVector& k_f_bin, Bin1D alpha_f_bin) const
{
    return m_factor*mp_form_factor->evaluate(k_i, k_f_bin, alpha_f_bin);
}

inline int FormFactorDecoratorFactor::getNumberOfStochasticParameters() const
{
    return mp_form_factor->getNumberOfStochasticParameters();
}

#endif /* FORMFACTORDECORATORFACTOR_H_ */



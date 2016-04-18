// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      FormFactors/inc/FormFactorDecoratorFactor.h
//! @brief     Defines class FormFactorDecoratorFactor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORDECORATORFACTOR_H_
#define FORMFACTORDECORATORFACTOR_H_

#include "IFormFactorDecorator.h"
#include "BornAgainNamespace.h"

//! @class FormFactorDecoratorFactor
//! @ingroup formfactors_internal
//! @brief Decorates a formfactor with a constant factor.

class BA_CORE_API_ FormFactorDecoratorFactor : public IFormFactorDecorator
{
public:
    FormFactorDecoratorFactor(const IFormFactor &form_factor, const complex_t factor);

    virtual ~FormFactorDecoratorFactor() {}

    virtual FormFactorDecoratorFactor *clone() const;

    virtual void accept(ISampleVisitor *visitor) const;

    //! Evaluate the form factor for scalar calculations
    virtual complex_t evaluate(const WavevectorInfo& wavevectors) const;

protected:
    complex_t m_factor;
};

inline FormFactorDecoratorFactor::FormFactorDecoratorFactor(const IFormFactor &form_factor,
                                                            const complex_t factor)
    : IFormFactorDecorator(form_factor), m_factor(factor)
{
    setName(BornAgain::FormFactorDecoratorFactorType);
}

inline FormFactorDecoratorFactor *FormFactorDecoratorFactor::clone() const
{
    return new FormFactorDecoratorFactor(*mp_form_factor, m_factor);
}

inline void FormFactorDecoratorFactor::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

inline complex_t FormFactorDecoratorFactor::evaluate(const WavevectorInfo& wavevectors) const
{
    return m_factor * mp_form_factor->evaluate(wavevectors);
}

#endif /* FORMFACTORDECORATORFACTOR_H_ */

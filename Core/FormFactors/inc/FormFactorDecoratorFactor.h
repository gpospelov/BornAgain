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

//! @class FormFactorDecoratorFactor
//! @ingroup formfactors_internal
//! @brief Decorates a formfactor with a constant factor.

class BA_CORE_API_ FormFactorDecoratorFactor : public IFormFactorDecorator
{
public:
    FormFactorDecoratorFactor(const IFormFactor &form_factor, const complex_t &factor);
    virtual ~FormFactorDecoratorFactor()
    {
    }
    virtual FormFactorDecoratorFactor *clone() const;
    virtual void accept(ISampleVisitor *visitor) const
    {
        visitor->visit(this);
    }

    //! Evaluate the form factor for scalar calculations
    virtual complex_t evaluate(const WavevectorInfo& wavevectors) const;

    virtual int getNumberOfStochasticParameters() const;

protected:
    complex_t m_factor;
};

inline FormFactorDecoratorFactor::FormFactorDecoratorFactor(const IFormFactor &form_factor,
                                                            const complex_t &factor)
    : IFormFactorDecorator(form_factor), m_factor(factor)
{
    setName("FormFactorDecoratorFactor");
}

inline FormFactorDecoratorFactor *FormFactorDecoratorFactor::clone() const
{
    FormFactorDecoratorFactor *result = new FormFactorDecoratorFactor(*mp_form_factor, m_factor);
    result->setName(getName());
    return result;
}

inline complex_t FormFactorDecoratorFactor::evaluate(const WavevectorInfo& wavevectors) const
{
    return m_factor * mp_form_factor->evaluate(wavevectors);
}

inline int FormFactorDecoratorFactor::getNumberOfStochasticParameters() const
{
    return mp_form_factor->getNumberOfStochasticParameters();
}

#endif /* FORMFACTORDECORATORFACTOR_H_ */

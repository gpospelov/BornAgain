// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/FormFactor/FormFactorDecoratorFactor.h
//! @brief     Defines class FormFactorDecoratorFactor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORDECORATORFACTOR_H
#define FORMFACTORDECORATORFACTOR_H

#include "IFormFactorDecorator.h"

//! Decorates a formfactor with a constant factor.
//!   Base class of FormFactorDecoratorMaterial.
//! @ingroup formfactors_internal

class BA_CORE_API_ FormFactorDecoratorFactor : public IFormFactorDecorator
{
public:
    FormFactorDecoratorFactor(const IFormFactor& form_factor, const complex_t factor);
    virtual ~FormFactorDecoratorFactor() {}
    virtual FormFactorDecoratorFactor* clone() const {
        return new FormFactorDecoratorFactor(*mp_form_factor, m_factor); }

    virtual void accept(ISampleVisitor* visitor) const { visitor->visit(this); }

    //! Evaluate the form factor for scalar calculations
    virtual complex_t evaluate(const WavevectorInfo& wavevectors) const;

protected:
    complex_t m_factor;
};

#endif // FORMFACTORDECORATORFACTOR_H

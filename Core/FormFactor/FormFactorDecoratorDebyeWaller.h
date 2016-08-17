// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/FormFactor/FormFactorDecoratorDebyeWaller.h
//! @brief     Defines and implements class FormFactorDecoratorDebyeWaller.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FORMFACTORDECORATORDEBYEWALLER_H
#define FORMFACTORDECORATORDEBYEWALLER_H

#include "IFormFactorDecorator.h"

//! @class FormFactorDecoratorDebyeWaller
//! @ingroup formfactors_internal
//! @brief Debye-Waller factors in radial and z directions.

class BA_CORE_API_ FormFactorDecoratorDebyeWaller : public IFormFactorDecorator
{
public:
    //! Isotropic Debye-Waller factor.
    FormFactorDecoratorDebyeWaller(const IFormFactor& form_factor, double dw_factor);

    //! Anisotropic Debye-Waller factor.
    FormFactorDecoratorDebyeWaller(const IFormFactor& form_factor, double dw_h_factor,
                                   double dw_r_factor);
//    ~FormFactorDecoratorDebyeWaller() final {}
    FormFactorDecoratorDebyeWaller* clone() const final {
        return new FormFactorDecoratorDebyeWaller(*mp_form_factor, m_h_dw_factor, m_r_dw_factor); }

    void accept(ISampleVisitor* visitor) const final { visitor->visit(this); }

    virtual complex_t evaluate(const WavevectorInfo& wavevectors) const;

protected:
    virtual void init_parameters();

private:
    double m_h_dw_factor; //!< the Debye-Waller factor in the z-direction
    double m_r_dw_factor; //!< the Debye-Waller factor in the radial direction
    void initialize();
};

#endif // FORMFACTORDECORATORDEBYEWALLER_H

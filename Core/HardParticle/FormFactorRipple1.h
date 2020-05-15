// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorRipple1.h
//! @brief     Defines class FormFactorRipple1.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef FORMFACTORRIPPLE1_H
#define FORMFACTORRIPPLE1_H

#include "ProfileRipple1.h"
#include "Ripples.h"

//! The form factor for a cosine ripple.
//! @ingroup legacyGrating

class BA_CORE_API_ FormFactorRipple1 : public ProfileRipple1
{
public:
    FormFactorRipple1(double length, double width, double height) :
        ProfileRipple1{length, width, height} {}

    FormFactorRipple1* clone() const override final
    {
        return new FormFactorRipple1(m_length, m_width, m_height);
    }
    void accept(INodeVisitor* visitor) const override final { visitor->visit(this); }

private:
    complex_t factor_x(complex_t qx) const override final {
        return ripples::factor_x_box(qx, m_length);
    }

};

#endif // FORMFACTORRIPPLE1_H

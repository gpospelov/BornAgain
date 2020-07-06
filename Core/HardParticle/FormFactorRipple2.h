// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorRipple2.h
//! @brief     Defines classes FormFactorRipple2*.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORRIPPLE2_H
#define BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORRIPPLE2_H

#include "Core/HardParticle/ProfileRipple2.h"

//! The form factor for a cosine ripple, with box profile in elongation direction.
//! @ingroup legacyGrating
class BA_CORE_API_ FormFactorRipple2Box : public ProfileRipple2
{
public:
    FormFactorRipple2Box(double length, double width, double height, double asymmetry);
    FormFactorRipple2Box* clone() const override final;
    void accept(INodeVisitor* visitor) const override final;

private:
    complex_t factor_x(complex_t qx) const override final;
};

//! The form factor for a cosine ripple, with Gaussian profile in elongation direction.
//! @ingroup legacyGrating
class BA_CORE_API_ FormFactorRipple2Gauss : public ProfileRipple2
{
public:
    FormFactorRipple2Gauss(double length, double width, double height, double asymmetry);
    FormFactorRipple2Gauss* clone() const override final;
    void accept(INodeVisitor* visitor) const override final;

private:
    complex_t factor_x(complex_t qx) const override final;
};

//! The form factor for a cosine ripple, with Lorentz form factor in elongation direction.
//! @ingroup legacyGrating
class BA_CORE_API_ FormFactorRipple2Lorentz : public ProfileRipple2
{
public:
    FormFactorRipple2Lorentz(double length, double width, double height, double asymmetry);
    FormFactorRipple2Lorentz* clone() const override final;
    void accept(INodeVisitor* visitor) const override final;

private:
    complex_t factor_x(complex_t qx) const override final;
};

#endif // BORNAGAIN_CORE_HARDPARTICLE_FORMFACTORRIPPLE2_H

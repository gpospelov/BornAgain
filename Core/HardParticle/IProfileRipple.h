// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/IProfileRipple.h
//! @brief     Defines interface classes IProfileRipple, ProfileRipple1, ProfileRipple2.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BORNAGAIN_CORE_HARDPARTICLE_PROFILERIPPLE2_H
#define BORNAGAIN_CORE_HARDPARTICLE_PROFILERIPPLE2_H

#include "Core/Scattering/IFormFactorBorn.h"

//! Base class for form factors with a cosine ripple profile in the yz plane.

class BA_CORE_API_ IProfileRipple : public IFormFactorBorn
{
public:
    IProfileRipple(double length, double width, double height);

    double getLength() const { return m_length; }
    double getHeight() const { return m_height; }
    double getWidth() const { return m_width; }

    double radialExtension() const override final;

    complex_t evaluate_for_q(cvector_t q) const override final;

protected:
    double m_length;
    double m_width;
    double m_height;

    virtual void onChange() override = 0;
    virtual complex_t factor_x(complex_t qx) const = 0;
    virtual complex_t factor_yz(complex_t qy, complex_t qz) const = 0;
};

//! Base class for form factors with a cosine ripple profile in the yz plane.

class BA_CORE_API_ ProfileRipple1 : public IProfileRipple
{
public:
    ProfileRipple1(double length, double width, double height);

private:
    virtual void onChange() override final;
    complex_t factor_yz(complex_t qy, complex_t qz) const final;
};

//! Base class for form factors with a triangular ripple profile in the yz plane.

class BA_CORE_API_ ProfileRipple2 : public IProfileRipple
{
public:
    ProfileRipple2(double length, double width, double height, double asymmetry);

    double getAsymmetry() const { return m_asymmetry; }

protected:
    double m_asymmetry;

private:
    virtual void onChange() override final;
    complex_t factor_yz(complex_t qy, complex_t qz) const final;
};

#endif // BORNAGAIN_CORE_HARDPARTICLE_PROFILERIPPLE2_H

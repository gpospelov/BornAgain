// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorRipple2.cpp
//! @brief     Implements classes FormFactorRipple2*.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/HardParticle/FormFactorRipple2.h"
#include "Core/HardParticle/Ripples.h"

// ************************************************************************** //
// class FormFactorRipple2Box
// ************************************************************************** //

FormFactorRipple2Box::FormFactorRipple2Box(
    double length, double width, double height, double asymmetry)
    : ProfileRipple2{length, width, height, asymmetry}
{
    setName(BornAgain::FFRipple2BoxType);
}

FormFactorRipple2Box* FormFactorRipple2Box::clone() const
{
    return new FormFactorRipple2Box(m_length, m_width, m_height, m_asymmetry);
}

void FormFactorRipple2Box::accept(INodeVisitor* visitor) const
{
    visitor->visit(this);
}

complex_t FormFactorRipple2Box::factor_x(complex_t qx) const
{
    return ripples::factor_x_box(qx, m_length);
}

// ************************************************************************** //
// class FormFactorRipple2Gauss
// ************************************************************************** //

FormFactorRipple2Gauss::FormFactorRipple2Gauss(
    double length, double width, double height, double asymmetry)
    : ProfileRipple2{length, width, height, asymmetry}
{
    setName(BornAgain::FFRipple2GaussType);
}

FormFactorRipple2Gauss* FormFactorRipple2Gauss::clone() const
{
    return new FormFactorRipple2Gauss(m_length, m_width, m_height, m_asymmetry);
}

void FormFactorRipple2Gauss::accept(INodeVisitor* visitor) const
{
    visitor->visit(this);
}

complex_t FormFactorRipple2Gauss::factor_x(complex_t qx) const
{
    return ripples::factor_x_Gauss(qx, m_length);
}

// ************************************************************************** //
// class FormFactorRipple2Lorentz
// ************************************************************************** //

FormFactorRipple2Lorentz::FormFactorRipple2Lorentz(
    double length, double width, double height, double asymmetry)
    : ProfileRipple2{length, width, height, asymmetry}
{
    setName(BornAgain::FFRipple2LorentzType);
}

FormFactorRipple2Lorentz* FormFactorRipple2Lorentz::clone() const
{
    return new FormFactorRipple2Lorentz(m_length, m_width, m_height, m_asymmetry);
}

void FormFactorRipple2Lorentz::accept(INodeVisitor* visitor) const
{
    visitor->visit(this);
}

complex_t FormFactorRipple2Lorentz::factor_x(complex_t qx) const
{
    return ripples::factor_x_Lorentz(qx, m_length);
}

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorEllipsoidalCylinder.cpp
//! @brief     Implements class FormFactorEllipsoidalCylinder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorEllipsoidalCylinder.h"
#include "BornAgainNamespace.h"
#include "DoubleEllipse.h"
#include "MathFunctions.h"
#include "MathConstants.h"
#include "RealParameter.h"

//! Constructor of a cylinder with an ellipse cross section.
//! @param radius_x: radius of the ellipse base in the x-direction, in nanometers
//! @param radius_y: radius of the ellipse base in the y-direction, in nanometers
//! @param height: height of the ellipsoidal cylinder in nanometers
FormFactorEllipsoidalCylinder::FormFactorEllipsoidalCylinder(
    double radius_x, double radius_y, double height)
    : m_radius_x(radius_x), m_radius_y(radius_y), m_height(height)
{
    setName(BornAgain::FFEllipsoidalCylinderType);
    registerParameter(BornAgain::RadiusX, &m_radius_x).setUnit(BornAgain::UnitsNm)
        .setNonnegative();
    registerParameter(BornAgain::RadiusY, & m_radius_y).setUnit(BornAgain::UnitsNm)
        .setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit(BornAgain::UnitsNm)
        .setNonnegative();
    onChange();
}

double FormFactorEllipsoidalCylinder::radialExtension() const
{
    return ( m_radius_x + m_radius_y ) / 2.0;
}

complex_t FormFactorEllipsoidalCylinder::evaluate_for_q(cvector_t q) const
{
    complex_t qxRa = q.x()*m_radius_x;
    complex_t qyRb = q.y()*m_radius_y;
    complex_t qzHdiv2 = m_height/2*q.z();

    complex_t Fz = exp_I(qzHdiv2) * MathFunctions::sinc(qzHdiv2);
    complex_t gamma  = std::sqrt((qxRa)*(qxRa) + (qyRb)*(qyRb));
    complex_t J1_gamma_div_gamma = MathFunctions::Bessel_J1c(gamma);

    return M_TWOPI *m_radius_x*m_radius_y*m_height * Fz*J1_gamma_div_gamma;
}

IFormFactor* FormFactorEllipsoidalCylinder::sliceFormFactor(ZLimits limits, const IRotation& rot,
                                                            kvector_t translation) const
{
    auto effects = computeSlicingEffects(limits, translation, m_height);
    FormFactorEllipsoidalCylinder slicedff(m_radius_x, m_radius_y,
                                           m_height - effects.dz_bottom - effects.dz_top);
    return CreateTransformedFormFactor(slicedff, rot, effects.position);
}

void FormFactorEllipsoidalCylinder::onChange()
{
    mP_shape.reset(new DoubleEllipse(m_radius_x, m_radius_y, m_height, m_radius_x, m_radius_y));
}

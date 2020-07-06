// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorCylinder.cpp
//! @brief     Implements class FormFactorCylinder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/HardParticle/FormFactorCylinder.h"
#include "Core/Basics/BornAgainNamespace.h"
#include "Core/Shapes/DoubleEllipse.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Tools/MathFunctions.h"
#include "Core/Parametrization/RealParameter.h"

//! Constructor of a cylinder with a circular base.
//! @param radius: radius of the circular base in nanometers
//! @param height: height of the cylinder in nanometers
FormFactorCylinder::FormFactorCylinder(double radius, double height)
    : m_radius(radius), m_height(height)
{
    setName(BornAgain::FFCylinderType);
    registerParameter(BornAgain::Radius, &m_radius).setUnit(BornAgain::UnitsNm).setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit(BornAgain::UnitsNm).setNonnegative();
    onChange();
}

complex_t FormFactorCylinder::evaluate_for_q(cvector_t q) const
{
    double R = m_radius;
    double H = m_height;

    complex_t qzH_half = q.z() * H / 2.0;
    complex_t z_part = H * MathFunctions::sinc(qzH_half) * exp_I(qzH_half);
    complex_t qxy = std::sqrt(q.x() * q.x() + q.y() * q.y());
    complex_t radial_part = M_TWOPI * R * R * MathFunctions::Bessel_J1c(qxy * R);
    complex_t result = radial_part * z_part;

    return result;
}

IFormFactor* FormFactorCylinder::sliceFormFactor(ZLimits limits, const IRotation& rot,
                                                 kvector_t translation) const
{
    auto effects = computeSlicingEffects(limits, translation, m_height);
    FormFactorCylinder slicedff(m_radius, m_height - effects.dz_bottom - effects.dz_top);
    return CreateTransformedFormFactor(slicedff, rot, effects.position);
}

void FormFactorCylinder::onChange()
{
    mP_shape.reset(new DoubleEllipse(m_radius, m_radius, m_height, m_radius, m_radius));
}

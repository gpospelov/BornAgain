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
#include "Rotations.h"

//! @param radius_x half length of one horizontal main axes
//! @param radius_y half length of the other horizontal main axes
//! @param height
FormFactorEllipsoidalCylinder::FormFactorEllipsoidalCylinder(
    double radius_x, double radius_y, double height)
    : m_radius_x(radius_x), m_radius_y(radius_y), m_height(height)
{
    setName(BornAgain::FFEllipsoidalCylinderType);
    registerParameter(BornAgain::RadiusX, &m_radius_x).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::RadiusY, & m_radius_y).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit("nm").setNonnegative();
    onChange();
}

double FormFactorEllipsoidalCylinder::getRadialExtension() const
{
    return ( m_radius_x + m_radius_y ) / 2.0;
}

complex_t FormFactorEllipsoidalCylinder::evaluate_for_q(const cvector_t q) const
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
    if (!IsZRotation(rot))
        throw std::runtime_error("FormFactorEllipsoidalCylinder::sliceFormFactor error: "
                                 "rotation is not along z-axis.");
    double dz_bottom = limits.zmin() - translation.z();
    double dz_top = translation.z() + m_height - limits.zmax();
    switch (limits.type()) {
    case ZLimits::FINITE:
    {
        if (dz_bottom < 0.0 || dz_bottom > m_height)
            throw std::runtime_error("FormFactorEllipsoidalCylinder::sliceFormFactor error: "
                                     "interface outside shape.");
        if (dz_top < 0.0 || dz_top > m_height)
            throw std::runtime_error("FormFactorEllipsoidalCylinder::sliceFormFactor error: "
                                     "interface outside shape.");
        if (dz_bottom + dz_top > m_height)
            throw std::runtime_error("FormFactorEllipsoidalCylinder::sliceFormFactor error: "
                                     "limits zmax < zmin.");
        FormFactorEllipsoidalCylinder slicedff(m_radius_x, m_radius_y,
                                               m_height - dz_bottom - dz_top);
        kvector_t position(translation.x(), translation.y(), limits.zmin());
        return CreateTransformedFormFactor(slicedff, rot, position);
    }
    case ZLimits::INFINITE:
    {
        throw std::runtime_error("FormFactorEllipsoidalCylinder::sliceFormFactor error: "
                                 "shape didn't need to be sliced.");
    }
    case ZLimits::POS_INFINITE:
    {
        if (dz_bottom < 0.0 || dz_bottom > m_height)
            throw std::runtime_error("FormFactorEllipsoidalCylinder::sliceFormFactor error: "
                                     "shape didn't need to be sliced.");
        FormFactorEllipsoidalCylinder slicedff(m_radius_x, m_radius_y, m_height - dz_bottom);
        kvector_t position(translation.x(), translation.y(), limits.zmin());
        return CreateTransformedFormFactor(slicedff, rot, position);
    }
    case ZLimits::NEG_INFINITE:
    {
        if (dz_top < 0.0 || dz_top > m_height)
            throw std::runtime_error("FormFactorEllipsoidalCylinder::sliceFormFactor error: "
                                     "shape didn't need to be sliced.");
        FormFactorEllipsoidalCylinder slicedff(m_radius_x, m_radius_y, m_height - dz_top);
        return CreateTransformedFormFactor(slicedff, rot, translation);
    }
    }
    return nullptr;
}

void FormFactorEllipsoidalCylinder::onChange()
{
    mP_shape.reset(new DoubleEllipse(m_radius_x, m_radius_y, m_height, m_radius_x, m_radius_y));
}

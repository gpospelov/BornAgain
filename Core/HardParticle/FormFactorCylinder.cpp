// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorCylinder.cpp
//! @brief     Implements class FormFactorCylinder.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorCylinder.h"
#include "BornAgainNamespace.h"
#include "DoubleEllipse.h"
#include "MathFunctions.h"
#include "MathConstants.h"
#include "RealParameter.h"
#include "Rotations.h"

FormFactorCylinder::FormFactorCylinder(double radius, double height)
    : m_radius(radius), m_height(height)
{
    setName(BornAgain::FFCylinderType);
    registerParameter(BornAgain::Radius, &m_radius).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit("nm").setNonnegative();
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
    if (!IsZRotation(rot))
        throw std::runtime_error("FormFactorCylinder::sliceFormFactor error: "
                                 "rotation is not along z-axis.");
    double dz_bottom = limits.zmin() - translation.z();
    double dz_top = translation.z() + m_height - limits.zmax();
    switch (limits.type()) {
    case ZLimits::FINITE:
    {
        if (dz_bottom < 0 && dz_top < 0)
            throw std::runtime_error("FormFactorCylinder::sliceFormFactor error: "
                                     "interface outside shape.");
        if (dz_bottom > m_height)
            throw std::runtime_error("FormFactorCylinder::sliceFormFactor error: "
                                     "interface outside shape.");
        if (dz_top > m_height)
            throw std::runtime_error("FormFactorCylinder::sliceFormFactor error: "
                                     "interface outside shape.");
        if (dz_bottom + dz_top > m_height)
            throw std::runtime_error("FormFactorCylinder::sliceFormFactor error: "
                                     "limits zmax < zmin.");
        kvector_t position(translation);
        if (dz_bottom < 0)
            dz_bottom = 0;
        else
            position.setZ(limits.zmin());
        if (dz_top < 0)
            dz_top = 0;
        FormFactorCylinder slicedff(m_radius, m_height - dz_bottom - dz_top);
        return CreateTransformedFormFactor(slicedff, rot, position);
    }
    case ZLimits::INFINITE:
    {
        throw std::runtime_error("FormFactorCylinder::sliceFormFactor error: "
                                 "shape didn't need to be sliced.");
    }
    case ZLimits::POS_INFINITE:
    {
        if (dz_bottom < 0.0 || dz_bottom > m_height)
            throw std::runtime_error("FormFactorCylinder::sliceFormFactor error: "
                                     "shape didn't need to be sliced.");
        FormFactorCylinder slicedff(m_radius, m_height - dz_bottom);
        kvector_t position(translation.x(), translation.y(), limits.zmin());
        return CreateTransformedFormFactor(slicedff, rot, position);
    }
    case ZLimits::NEG_INFINITE:
    {
        if (dz_top < 0.0 || dz_top > m_height)
            throw std::runtime_error("FormFactorCylinder::sliceFormFactor error: "
                                     "shape didn't need to be sliced.");
        FormFactorCylinder slicedff(m_radius, m_height - dz_top);
        return CreateTransformedFormFactor(slicedff, rot, translation);
    }
    }
    return nullptr;
}

void FormFactorCylinder::onChange()
{
    mP_shape.reset(new DoubleEllipse(m_radius, m_radius, m_height, m_radius, m_radius));
}

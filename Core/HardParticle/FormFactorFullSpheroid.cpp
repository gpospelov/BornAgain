// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorFullSpheroid.cpp
//! @brief     Implements class FormFactorFullSpheroid.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorFullSpheroid.h"
#include "BornAgainNamespace.h"
#include "FormFactorTruncatedSpheroid.h"
#include "MathFunctions.h"
#include "MathConstants.h"
#include "RealParameter.h"
#include "Rotations.h"
#include "TruncatedEllipsoid.h"
#include <limits>

//! @param radius of the two equal axes
//! @param height total height of the spheroid, i.e. twice the radius of the third axis
FormFactorFullSpheroid::FormFactorFullSpheroid(double radius, double height )
    : m_radius(radius), m_height(height)
{
    setName(BornAgain::FFFullSpheroidType);
    registerParameter(BornAgain::Radius, &m_radius).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit("nm").setNonnegative();
    mP_integrator = make_integrator_complex(this, &FormFactorFullSpheroid::Integrand);
    onChange();
}

//! Integrand for complex formfactor.
complex_t FormFactorFullSpheroid::Integrand(double Z) const
{
    double R = m_radius;
    double H = m_height;

    double Rz  = R*std::sqrt(1-4.0*Z*Z/(H*H));
    complex_t qxy = std::sqrt(m_q.x()*m_q.x()+m_q.y()*m_q.y());
    complex_t qrRz = qxy*Rz;
    complex_t J1_qrRz_div_qrRz = MathFunctions::Bessel_J1c(qrRz);

    return Rz*Rz* J1_qrRz_div_qrRz *std::cos(m_q.z()*Z);
}

complex_t FormFactorFullSpheroid::evaluate_for_q(cvector_t q) const
{
    double H = m_height;
    double R = m_radius;
    m_q = q;

    if (std::abs(m_q.mag()) <= std::numeric_limits<double>::epsilon())
        return M_TWOPI*R*R*H/3.;
    complex_t qzH_half = H/2*q.z();
    return 4 * M_PI * mP_integrator->integrate(0.0, H/2.0) * exp_I(qzH_half);
}

IFormFactor*FormFactorFullSpheroid:: sliceFormFactor(ZLimits limits, const IRotation& rot,
                                                     kvector_t translation) const
{
    if (!IsZRotation(rot))
        throw std::runtime_error("FormFactorFullSpheroid::sliceFormFactor error: "
                                 "rotation is not along z-axis.");
    double flattening = m_height/(2.0*m_radius);
    double dz_bottom = limits.zmin() - translation.z();
    double dz_top = translation.z() + m_height - limits.zmax();
    switch (limits.type()) {
    case ZLimits::FINITE:
    {
        if (dz_bottom < 0.0 || dz_bottom > m_height)
            throw std::runtime_error("FormFactorFullSpheroid::sliceFormFactor error: "
                                     "interface outside shape.");
        if (dz_top < 0.0 || dz_top > m_height)
            throw std::runtime_error("FormFactorFullSpheroid::sliceFormFactor error: "
                                     "interface outside shape.");
        if (dz_bottom + dz_top > m_height)
            throw std::runtime_error("FormFactorFullSpheroid::sliceFormFactor error: "
                                     "limits zmax < zmin.");
        FormFactorTruncatedSpheroid slicedff(m_radius, m_height - dz_bottom, flattening, dz_top);
        kvector_t position(translation.x(), translation.y(), limits.zmin());
        return CreateTransformedFormFactor(slicedff, rot, position);
    }
    case ZLimits::INFINITE:
    {
        throw std::runtime_error("FormFactorFullSpheroid::sliceFormFactor error: "
                                 "shape didn't need to be sliced.");
    }
    case ZLimits::POS_INFINITE:
    {
        if (dz_bottom < 0.0 || dz_bottom > m_height)
            throw std::runtime_error("FormFactorFullSpheroid::sliceFormFactor error: "
                                     "shape didn't need to be sliced.");
        FormFactorTruncatedSpheroid slicedff(m_radius, m_height - dz_bottom, flattening, 0.0);
        kvector_t position(translation.x(), translation.y(), limits.zmin());
        return CreateTransformedFormFactor(slicedff, rot, position);
    }
    case ZLimits::NEG_INFINITE:
    {
        if (dz_top < 0.0 || dz_top > m_height)
            throw std::runtime_error("FormFactorFullSpheroid::sliceFormFactor error: "
                                     "shape didn't need to be sliced.");
        FormFactorTruncatedSpheroid slicedff(m_radius, m_height, flattening, dz_top);
        return CreateTransformedFormFactor(slicedff, rot, translation);
    }
    }
    return nullptr;
}

void FormFactorFullSpheroid::onChange()
{
    mP_shape.reset(new TruncatedEllipsoid(m_radius, m_radius, m_height/2.0, m_height, 0.0));
}

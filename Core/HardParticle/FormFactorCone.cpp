// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorCone.cpp
//! @brief     Implements class FormFactorCone.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorCone.h"
#include "BornAgainNamespace.h"
#include "DoubleEllipse.h"
#include "Exceptions.h"
#include "MathFunctions.h"
#include "MathConstants.h"
#include "RealParameter.h"
#include "Rotations.h"
#include <limits>

//! @param radius of circular base
//! @param height of frustum
//! @param alpha  angle in radians between base and lateral surface
FormFactorCone::FormFactorCone(double radius, double height, double alpha)
    : m_radius(radius), m_height(height), m_alpha(alpha)
{
    setName(BornAgain::FFConeType);
    m_cot_alpha = MathFunctions::cot(m_alpha);
    if( !std::isfinite(m_cot_alpha) || m_cot_alpha<0 )
        throw Exceptions::OutOfBoundsException("pyramid angle alpha out of bounds");
    if(m_cot_alpha*m_height > m_radius) {
        std::ostringstream ostr;
        ostr << "FormFactorCone() -> Error in class initialization ";
        ostr << "with parameters radius:" << m_radius;
        ostr << " m_height:" << m_height;
        ostr << " alpha[rad]:" << m_alpha << "\n\n";
        ostr << "Check for 'height <= radius*tan(alpha)' failed.";
        throw Exceptions::ClassInitializationException(ostr.str());
    }
    registerParameter(BornAgain::Radius, &m_radius).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::Height, &m_height).setUnit("nm").setNonnegative();
    registerParameter(BornAgain::Alpha, & m_alpha).setUnit("rad").setLimited(0., M_PI_2);

    mP_integrator = make_integrator_complex(this, &FormFactorCone::Integrand);
    onChange();
}

//! Integrand for complex formfactor.
complex_t FormFactorCone::Integrand(double Z) const
{
    double Rz = m_radius - Z*m_cot_alpha;
    complex_t q_p = std::sqrt(m_q.x()*m_q.x()+m_q.y()*m_q.y()); // sqrt(x*x + y*y)
    return Rz*Rz*MathFunctions::Bessel_J1c(q_p*Rz) * exp_I(m_q.z()*Z);
}

complex_t FormFactorCone::evaluate_for_q(cvector_t q) const
{
    m_q = q;
    if ( std::abs(m_q.mag()) < std::numeric_limits<double>::epsilon()) {
        double R = m_radius;
        double H = m_height;
        double tga = std::tan(m_alpha);
        double HdivRtga = H/tga/R; // TODO preclude division by zero WAITING fuller refactoring

        return  M_PI/3.0*tga*R*R*R*
                (1.0 - (1.0 - HdivRtga)*(1.0 - HdivRtga)*(1.0 - HdivRtga));
    } else {
        complex_t integral = mP_integrator->integrate(0., m_height);
        return M_TWOPI*integral;
    }
}

IFormFactor* FormFactorCone::sliceFormFactor(ZLimits limits, const IRotation& rot,
                                            kvector_t translation) const
{
    if (!IsZRotation(rot))
        throw std::runtime_error("FormFactorCone::sliceFormFactor error: "
                                 "rotation is not along z-axis.");
    double dz_bottom = limits.zmin() - translation.z();
    double dz_top = translation.z() + m_height - limits.zmax();
    switch (limits.type()) {
    case ZLimits::FINITE:
    {
        if (dz_bottom < 0.0 || dz_bottom > m_height)
            throw std::runtime_error("FormFactorCone::sliceFormFactor error: "
                                     "interface outside shape.");
        if (dz_top < 0.0 || dz_top > m_height)
            throw std::runtime_error("FormFactorCone::sliceFormFactor error: "
                                     "interface outside shape.");
        if (dz_bottom + dz_top > m_height)
            throw std::runtime_error("FormFactorCone::sliceFormFactor error: "
                                     "limits zmax < zmin.");
        double dradius = dz_bottom*m_cot_alpha;
        FormFactorCone slicedff(m_radius - dradius, m_height - dz_bottom - dz_top, m_alpha);
        kvector_t position(translation.x(), translation.y(), limits.zmin());
        return CreateTransformedFormFactor(slicedff, rot, position);
    }
    case ZLimits::INFINITE:
    {
        throw std::runtime_error("FormFactorCone::sliceFormFactor error: "
                                 "shape didn't need to be sliced.");
    }
    case ZLimits::POS_INFINITE:
    {
        if (dz_bottom < 0.0 || dz_bottom > m_height)
            throw std::runtime_error("FormFactorCone::sliceFormFactor error: "
                                     "shape didn't need to be sliced.");
        double dradius = dz_bottom*m_cot_alpha;
        FormFactorCone slicedff(m_radius - dradius, m_height - dz_bottom, m_alpha);
        kvector_t position(translation.x(), translation.y(), limits.zmin());
        return CreateTransformedFormFactor(slicedff, rot, position);
    }
    case ZLimits::NEG_INFINITE:
    {
        if (dz_top < 0.0 || dz_top > m_height)
            throw std::runtime_error("FormFactorCone::sliceFormFactor error: "
                                     "shape didn't need to be sliced.");
        FormFactorCone slicedff(m_radius, m_height - dz_top, m_alpha);
        return CreateTransformedFormFactor(slicedff, rot, translation);
    }
    }
    return nullptr;
}

void FormFactorCone::onChange()
{
    m_cot_alpha = MathFunctions::cot(m_alpha);
    double radius2 = m_radius - m_height*m_cot_alpha;
    mP_shape.reset(new DoubleEllipse(m_radius, m_radius, m_height, radius2, radius2));
}

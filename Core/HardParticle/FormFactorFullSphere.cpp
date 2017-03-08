// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorFullSphere.cpp
//! @brief     Implements class FormFactorFullSphere.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015-16
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FormFactorFullSphere.h"
#include "FormFactorTruncatedSphere.h"
#include "FormFactorWeighted.h"
#include "BornAgainNamespace.h"
#include "MathConstants.h"
#include "RealParameter.h"
#include "Rotations.h"
#include "TruncatedEllipsoid.h"

FormFactorFullSphere::FormFactorFullSphere(double radius)
    : m_radius(radius)
{
    setName(BornAgain::FFFullSphereType);
    registerParameter(BornAgain::Radius, &m_radius).setUnit("nm").setNonnegative();
    mP_shape.reset(new TruncatedEllipsoid(radius, radius, radius, 2.0*radius, 0.0));
    onChange();
}

double FormFactorFullSphere::bottomZ(const IRotation& rotation) const
{
    kvector_t centre(0.0, 0.0, m_radius);
    kvector_t new_centre = rotation.getTransform3D().transformed(centre);
    return new_centre.z() - m_radius;
}

double FormFactorFullSphere::topZ(const IRotation& rotation) const
{
    kvector_t centre(0.0, 0.0, m_radius);
    kvector_t new_centre = rotation.getTransform3D().transformed(centre);
    return new_centre.z() + m_radius;
}

complex_t FormFactorFullSphere::evaluate_for_q(cvector_t q) const
{
    double R = m_radius;
    complex_t q1 = sqrt( q.x()*q.x() + q.y()*q.y() + q.z()*q.z() ); // NO sesquilinear dot product!
    complex_t qR = q1*R;

    complex_t ret;
    if (std::abs(qR) < 1e-4) { // relative error is O(qR^4) with small prefactor
#ifdef POLYHEDRAL_DIAGNOSTIC
        diagnosis = { 0, 1 };
#endif
        ret = 4*M_PI/3*pow(R,3) * ( 1. - 0.1*pow(qR,2) );
    }
    else {
#ifdef POLYHEDRAL_DIAGNOSTIC
        diagnosis = { 0, 0 };
#endif
        ret = 4*M_PI*pow(q1,-3)*(sin(qR) - qR*cos(qR));
    }

    return exp_I(q.z()*R) * ret;
}

IFormFactor* FormFactorFullSphere::sliceFormFactor(ZLimits limits, const IRotation& rot,
                                                   kvector_t translation) const
{
    kvector_t centre(0.0, 0.0, m_radius);
    kvector_t new_centre = rot.getTransform3D().transformed(centre);
    kvector_t new_basis = new_centre - kvector_t(0.0, 0.0, m_radius);
    kvector_t new_translation = translation + new_basis;
    std::unique_ptr<IRotation> P_identity(IRotation::createIdentity());
    double height = 2.0*m_radius;
    double dz_bottom = limits.zmin() - new_translation.z();
    double dz_top = new_translation.z() + height - limits.zmax();
    switch (limits.type()) {
    case ZLimits::FINITE:
    {
        if (dz_bottom < 0 && dz_top < 0)
            throw std::runtime_error("FormFactorFullSphere::sliceFormFactor error: "
                                     "interface outside shape.");
        if (dz_bottom > height)
            throw std::runtime_error("FormFactorFullSphere::sliceFormFactor error: "
                                     "interface outside shape.");
        if (dz_top > height)
            throw std::runtime_error("FormFactorFullSphere::sliceFormFactor error: "
                                     "interface outside shape.");
        if (dz_bottom + dz_top > height)
            throw std::runtime_error("FormFactorFullSphere::sliceFormFactor error: "
                                     "limits zmax < zmin.");
        kvector_t position(new_translation);
        if (dz_bottom < 0)
            dz_bottom = 0;
        else
            position.setZ(limits.zmin());
        if (dz_top < 0)
            dz_top = 0;
        FormFactorTruncatedSphere slicedff(m_radius, height - dz_bottom, dz_top);
        return CreateTransformedFormFactor(slicedff, *P_identity, position);
    }
    case ZLimits::INFINITE:
    {
        throw std::runtime_error("FormFactorFullSphere::sliceFormFactor error: "
                                 "shape didn't need to be sliced.");
    }
    case ZLimits::POS_INFINITE:
    {
        if (dz_bottom < 0.0 || dz_bottom > height)
            throw std::runtime_error("FormFactorFullSphere::sliceFormFactor error: "
                                     "shape didn't need to be sliced.");
        FormFactorTruncatedSphere slicedff(m_radius, height - dz_bottom);
        kvector_t position(new_translation.x(), new_translation.y(), limits.zmin());
        return CreateTransformedFormFactor(slicedff, *P_identity, position);
    }
    case ZLimits::NEG_INFINITE:
    {
        if (dz_top < 0.0 || dz_top > height)
            throw std::runtime_error("FormFactorFullSphere::sliceFormFactor error: "
                                     "shape didn't need to be sliced.");
        FormFactorTruncatedSphere slicedff(m_radius, height, dz_top);
        return CreateTransformedFormFactor(slicedff, *P_identity, new_translation);
    }
    }
    return nullptr;
}

void FormFactorFullSphere::onChange()
{
    mP_shape.reset(new TruncatedEllipsoid(m_radius, m_radius, m_radius, 2.0*m_radius, 0.0));
}

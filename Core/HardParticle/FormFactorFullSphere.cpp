// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/HardParticle/FormFactorFullSphere.cpp
//! @brief     Implements class FormFactorFullSphere.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/HardParticle/FormFactorFullSphere.h"
#include "Core/Basics/BornAgainNamespace.h"
#include "Core/HardParticle/FormFactorTruncatedSphere.h"
#include "Core/Particle/FormFactorWeighted.h"
#include "Core/Basics/MathConstants.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Scattering/Rotations.h"

//! Constructor of a full sphere.
//! @param radius: radius of the sphere in nanometers
FormFactorFullSphere::FormFactorFullSphere(double radius, bool position_at_center)
    : m_radius(radius), m_position_at_center(position_at_center)
{
    setName(BornAgain::FFFullSphereType);
    registerParameter(BornAgain::Radius, &m_radius).setUnit(BornAgain::UnitsNm).setNonnegative();
    onChange();
}

double FormFactorFullSphere::bottomZ(const IRotation& rotation) const
{
    if (m_position_at_center)
        return -m_radius;
    kvector_t centre(0.0, 0.0, m_radius);
    kvector_t new_centre = rotation.getTransform3D().transformed(centre);
    return new_centre.z() - m_radius;
}

double FormFactorFullSphere::topZ(const IRotation& rotation) const
{
    if (m_position_at_center)
        return m_radius;
    kvector_t centre(0.0, 0.0, m_radius);
    kvector_t new_centre = rotation.getTransform3D().transformed(centre);
    return new_centre.z() + m_radius;
}

complex_t FormFactorFullSphere::evaluate_for_q(cvector_t q) const
{
    double R = m_radius;
    complex_t q1 =
        sqrt(q.x() * q.x() + q.y() * q.y() + q.z() * q.z()); // NO sesquilinear dot product!
    complex_t qR = q1 * R;

    complex_t ret;
    if (std::abs(qR) < 1e-4) { // relative error is O(qR^4) with small prefactor
#ifdef POLYHEDRAL_DIAGNOSTIC
        diagnosis = {0, 1};
#endif
        // expand sin(qR)-qR*cos(qR) up to qR^5
        ret = 4 * M_PI / 3 * pow(R, 3) * (1. - 0.1 * pow(qR, 2));
    } else {
#ifdef POLYHEDRAL_DIAGNOSTIC
        diagnosis = {0, 0};
#endif
        ret = 4 * M_PI * pow(q1, -3) * (sin(qR) - qR * cos(qR));
    }
    auto prefactor = m_position_at_center ? 1.0 : exp_I(q.z() * R);
    return prefactor * ret;
}

IFormFactor* FormFactorFullSphere::sliceFormFactor(ZLimits limits, const IRotation& rot,
                                                   kvector_t translation) const
{
    kvector_t center(0.0, 0.0, m_radius);
    kvector_t rotation_offset = m_position_at_center
                                    ? kvector_t(0.0, 0.0, 0.0)
                                    : rot.getTransform3D().transformed(center) - center;
    kvector_t new_translation = translation + rotation_offset;
    std::unique_ptr<IRotation> P_identity(IRotation::createIdentity());
    double height = 2.0 * m_radius;
    auto effects = computeSlicingEffects(limits, new_translation, height);
    FormFactorTruncatedSphere slicedff(m_radius, height - effects.dz_bottom, effects.dz_top);
    return CreateTransformedFormFactor(slicedff, *P_identity, effects.position);
}

void FormFactorFullSphere::onChange() {}

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Scattering/Rotations.cpp
//! @brief     Implements IRotation classes.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "Core/Scattering/Rotations.h"
#include "Core/Basics/Assert.h"
#include "Core/Parametrization/RealParameter.h"
#include "Core/Vector/Transform3D.h"

IRotation::IRotation(const INode* parent, const std::vector<const char*>& PName,
                     const std::vector<const char*>& PUnit, const std::vector<double>& PMin,
                     const std::vector<double>& PMax, const std::vector<double>& PDefault,
                     const std::vector<double>& P)
    : INode{parent, PName, PUnit, PMin, PMax, PDefault, P}
{
}

IRotation* IRotation::createRotation(const Transform3D& transform)
{
    auto rot_type = transform.getRotationType();
    switch (rot_type) {
    case Transform3D::XAXIS: {
        double angle = transform.calculateRotateXAngle();
        return new RotationX(angle);
    }
    case Transform3D::YAXIS: {
        double angle = transform.calculateRotateYAngle();
        return new RotationY(angle);
    }
    case Transform3D::ZAXIS: {
        double angle = transform.calculateRotateZAngle();
        return new RotationZ(angle);
    }
    case Transform3D::EULER: {
        double alpha, beta, gamma;
        transform.calculateEulerAngles(&alpha, &beta, &gamma);
        return new RotationEuler(alpha, beta, gamma);
    }
    }
    ASSERT(0); // impossible case
}

IRotation* IRotation::createIdentity()
{
    return new RotationZ(0.0);
}

kvector_t IRotation::transformed(const kvector_t& v) const
{
    return getTransform3D().transformed(v);
}

bool IRotation::isIdentity() const
{
    return getTransform3D().isIdentity();
}

bool IRotation::zInvariant() const
{
    return getTransform3D().isZRotation();
}

//! Returns concatenated rotation (first right, then left).

IRotation* createProduct(const IRotation& left, const IRotation& right)
{
    Transform3D tr_left = left.getTransform3D();
    Transform3D tr_right = right.getTransform3D();
    IRotation* p_result = IRotation::createRotation(tr_left * tr_right);
    return p_result;
}

// --- IdentityRotation -------------------------------------------------------

Transform3D IdentityRotation::getTransform3D() const
{
    return Transform3D::createIdentity();
}

// --- RotationX --------------------------------------------------------------

//! Constructor of rotation around x-axis
//! @param angle: rotation angle around x-axis in radians
RotationX::RotationX(double angle) : m_angle(angle)
{
    setName("XRotation");
    registerParameter("Angle", &m_angle).setUnit("rad");
}

Transform3D RotationX::getTransform3D() const
{
    return Transform3D::createRotateX(m_angle);
}

// --- RotationY --------------------------------------------------------------

//! Constructor of rotation around y-axis
//! @param angle: rotation angle around y-axis in radians
RotationY::RotationY(double angle) : m_angle(angle)
{
    setName("YRotation");
    registerParameter("Angle", &m_angle).setUnit("rad");
}

Transform3D RotationY::getTransform3D() const
{
    return Transform3D::createRotateY(m_angle);
}

// --- RotationZ --------------------------------------------------------------

//! Constructor of rotation around z-axis
//! @param angle: rotation angle around z-axis in radians
RotationZ::RotationZ(double angle) : m_angle(angle)
{
    setName("ZRotation");
    registerParameter("Angle", &m_angle).setUnit("rad");
}

Transform3D RotationZ::getTransform3D() const
{
    return Transform3D::createRotateZ(m_angle);
}

// --- RotationEuler ----------------------------------------------------------

//! Constructor of Euler rotation (sequence of three rotations following Euler angles
//! notation z-x'-z').
//! @param alpha: first Euler angle in radians
//! @param beta: second Euler angle in radians
//! @param gamma: third Euler angle in radians
RotationEuler::RotationEuler(double alpha, double beta, double gamma)
    : m_alpha(alpha), m_beta(beta), m_gamma(gamma)
{
    setName("EulerRotation");
    registerParameter("Alpha", &m_alpha).setUnit("rad");
    registerParameter("Beta", &m_beta).setUnit("rad");
    registerParameter("Gamma", &m_gamma).setUnit("rad");
}

IRotation* RotationEuler::createInverse() const
{
    Transform3D inverse_transform(getTransform3D().getInverse());
    return createRotation(inverse_transform);
}

Transform3D RotationEuler::getTransform3D() const
{
    return Transform3D::createRotateEuler(m_alpha, m_beta, m_gamma);
}

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Samples/Rotations.cpp
//! @brief     Implements IRotation classes.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Rotations.h"
#include "BornAgainNamespace.h"

using namespace BornAgain;

IRotation *IRotation::createRotation(const Geometry::Transform3D &transform)
{
    double alpha, beta, gamma;
    transform.calculateEulerAngles(&alpha, &beta, &gamma);
    Geometry::Transform3D::ERotationType rot_type = transform.getRotationType();
    switch (rot_type) {
    case Geometry::Transform3D::XAXIS:
        if (alpha>0.0) beta = -beta;
        return new RotationX(beta);
    case Geometry::Transform3D::YAXIS:
        if (alpha>0.0 && alpha<3.14) beta = -beta;
        return new RotationY(beta);
    case Geometry::Transform3D::ZAXIS:
        return new RotationZ(alpha);
    default:
        return new RotationEuler(alpha, beta, gamma);
    }
}

void IRotation::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

bool IRotation::isIdentity() const
{
    return getTransform3D().isIdentity();
}

//! Returns concatenated rotation (first right, then left).

IRotation *CreateProduct(const IRotation &left, const IRotation &right)
{
    Geometry::Transform3D tr_left = left.getTransform3D();
    Geometry::Transform3D tr_right = right.getTransform3D();
    IRotation *p_result = IRotation::createRotation(tr_left*tr_right);
    return p_result;
}

// --- RotationX --------------------------------------------------------------

RotationX::RotationX(double angle)
    : m_angle(angle)
{
    setName(XRotationType);
    init_parameters();
}

RotationX *RotationX::clone() const
{
    return new RotationX(m_angle);
}

RotationX *RotationX::cloneInvertB() const
{
    return clone();
}

RotationX *RotationX::createInverse() const
{
    return new RotationX(-m_angle);
}

double RotationX::getAngle() const
{
    return m_angle;
}

void RotationX::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

Geometry::Transform3D RotationX::getTransform3D() const
{
    return Geometry::Transform3D::createRotateX(m_angle);
}

void RotationX::init_parameters()
{
    clearParameterPool();
    registerParameter(Angle, &m_angle);
}

// --- RotationY --------------------------------------------------------------

RotationY::RotationY(double angle)
    : m_angle(angle)
{
    setName(YRotationType);
    init_parameters();
}

RotationY *RotationY::clone() const
{
    return new RotationY(m_angle);
}

RotationY *RotationY::cloneInvertB() const
{
    return clone();
}

RotationY *RotationY::createInverse() const
{
    return new RotationY(-m_angle);
}

double RotationY::getAngle() const
{
    return m_angle;
}

void RotationY::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

Geometry::Transform3D RotationY::getTransform3D() const
{
    return Geometry::Transform3D::createRotateY(m_angle);
}

void RotationY::init_parameters()
{
    clearParameterPool();
    registerParameter(Angle, &m_angle);
}

// --- RotationZ --------------------------------------------------------------

RotationZ::RotationZ(double angle)
    : m_angle(angle)
{
    setName(ZRotationType);
    init_parameters();
}

RotationZ *RotationZ::clone() const
{
    return new RotationZ(m_angle);
}

RotationZ *RotationZ::cloneInvertB() const
{
    return clone();
}

RotationZ *RotationZ::createInverse() const
{
    return new RotationZ(-m_angle);
}

double RotationZ::getAngle() const
{
    return m_angle;
}

void RotationZ::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

Geometry::Transform3D RotationZ::getTransform3D() const
{
    return Geometry::Transform3D::createRotateZ(m_angle);
}

void RotationZ::init_parameters()
{
    clearParameterPool();
    registerParameter(Angle, &m_angle);
}

// --- RotationEuler ----------------------------------------------------------

RotationEuler::RotationEuler(double alpha, double beta, double gamma)
    : m_alpha(alpha)
    , m_beta(beta)
    , m_gamma(gamma)
{
    setName(EulerRotationType);
    init_parameters();
}

RotationEuler *RotationEuler::clone() const
{
    return new RotationEuler(m_alpha, m_beta, m_gamma);
}

RotationEuler *RotationEuler::cloneInvertB() const
{
    return clone();
}

IRotation *RotationEuler::createInverse() const
{
    Geometry::Transform3D inverse_transform(getTransform3D().getInverse());
    return createRotation(inverse_transform);
}

double RotationEuler::getAlpha() const
{
    return m_alpha;
}

double RotationEuler::getBeta() const
{
    return m_beta;
}

double RotationEuler::getGamma() const
{
    return m_gamma;
}

void RotationEuler::accept(ISampleVisitor *visitor) const
{
    visitor->visit(this);
}

Geometry::Transform3D RotationEuler::getTransform3D() const
{
    return Geometry::Transform3D::createRotateEuler(m_alpha, m_beta, m_gamma);
}

void RotationEuler::init_parameters()
{
    clearParameterPool();
    registerParameter(Alpha, &m_alpha);
    registerParameter(Beta, &m_beta);
    registerParameter(Gamma, &m_gamma);
}

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/Rotations.cpp
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

#include <boost/scoped_ptr.hpp>


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

IRotation &operator*(const IRotation &left, const IRotation &right)
{
    boost::scoped_ptr<Geometry::Transform3D> tr_left(left.createTransform3D());
    boost::scoped_ptr<Geometry::Transform3D> tr_right(right.createTransform3D());
    IRotation *p_result = IRotation::createRotation((*tr_left)*(*tr_right));
    return *p_result;
}


RotationX::RotationX(double angle)
    : m_angle(angle)
{
    setName("RotationX");
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

Geometry::Transform3D *RotationX::createTransform3D() const
{
    return Geometry::Transform3D::createRotateX(m_angle).clone();
}

void RotationX::init_parameters()
{
    clearParameterPool();
    registerParameter("angle", &m_angle);
}

RotationY::RotationY(double angle)
    : m_angle(angle)
{
    setName("RotationY");
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

Geometry::Transform3D *RotationY::createTransform3D() const
{
    return Geometry::Transform3D::createRotateY(m_angle).clone();
}

void RotationY::init_parameters()
{
    clearParameterPool();
    registerParameter("angle", &m_angle);
}

RotationZ::RotationZ(double angle)
    : m_angle(angle)
{
    setName("RotationZ");
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

Geometry::Transform3D *RotationZ::createTransform3D() const
{
    return Geometry::Transform3D::createRotateZ(m_angle).clone();
}

void RotationZ::init_parameters()
{
    clearParameterPool();
    registerParameter("angle", &m_angle);
}

RotationEuler::RotationEuler(double alpha, double beta, double gamma)
    : m_alpha(alpha)
    , m_beta(beta)
    , m_gamma(gamma)
{
    setName("RotationEuler");
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

Geometry::Transform3D *RotationEuler::createTransform3D() const
{
    return Geometry::Transform3D::createRotateEuler(m_alpha, m_beta, m_gamma).clone();
}

void RotationEuler::init_parameters()
{
    clearParameterPool();
    registerParameter("alpha", &m_alpha);
    registerParameter("beta", &m_beta);
    registerParameter("gamma", &m_gamma);
}

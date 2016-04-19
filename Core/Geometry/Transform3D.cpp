// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file       Geometry/Transform3D.cpp
//! @brief      Implements template class Transform3D.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Transform3D.h"

#include <Eigen/LU>


Geometry::Transform3D::Transform3D()
{
    m_matrix.setIdentity();
    m_inverse_matrix.setIdentity();
}

Geometry::Transform3D::Transform3D(const Transform3D& other)
: m_matrix(other.m_matrix)
, m_inverse_matrix(other.m_inverse_matrix)
{
}

Geometry::Transform3D Geometry::Transform3D::createIdentity()
{
    return Geometry::Transform3D();
}

Geometry::Transform3D Geometry::Transform3D::createRotateX(double phi)
{
    double cosine = std::cos(phi);
    double sine = std::sin(phi);
    Eigen::Matrix3d matrix;
    matrix.setIdentity();
    matrix(1,1) = cosine;
    matrix(1,2) = -sine;
    matrix(2,1) = sine;
    matrix(2,2) = cosine;
    return Transform3D(matrix);
}

Geometry::Transform3D Geometry::Transform3D::createRotateY(double phi)
{
    double cosine = std::cos(phi);
    double sine = std::sin(phi);
    Eigen::Matrix3d matrix;
    matrix.setIdentity();
    matrix(0,0) = cosine;
    matrix(0,2) = sine;
    matrix(2,0) = -sine;
    matrix(2,2) = cosine;
    return Transform3D(matrix);
}

Geometry::Transform3D Geometry::Transform3D::createRotateZ(double phi)
{
    double cosine = std::cos(phi);
    double sine = std::sin(phi);
    Eigen::Matrix3d matrix;
    matrix.setIdentity();
    matrix(0,0) = cosine;
    matrix(0,1) = -sine;
    matrix(1,0) = sine;
    matrix(1,1) = cosine;
    return Transform3D(matrix);
}

Geometry::Transform3D Geometry::Transform3D::createRotateEuler(
    double alpha, double beta, double gamma)
{
    Transform3D zrot = createRotateZ(alpha);
    Transform3D xrot = createRotateX(beta);
    Transform3D zrot2 = createRotateZ(gamma);
    return zrot2*xrot*zrot;
}

void Geometry::Transform3D::calculateEulerAngles(
    double *p_alpha, double *p_beta, double *p_gamma) const
{
    // First check if second angle is zero or pi
    if (m_matrix(2,0)==0.0 && m_matrix(2,1)==0.0) {
        *p_alpha = std::atan2(-m_matrix(0,1), m_matrix(0,0));
        *p_beta = std::acos(m_matrix(2,2));
        *p_gamma = 0.0;
    } else {
        *p_alpha = std::atan2(m_matrix(2,0), m_matrix(2,1));
        *p_beta = std::acos(m_matrix(2,2));
        *p_gamma = std::atan2(m_matrix(0,2), -m_matrix(1,2));
    }
}

Geometry::Transform3D Geometry::Transform3D::getInverse() const
{
    Transform3D result(m_inverse_matrix);
    return result;
}

Geometry::BasicVector3D<double> Geometry::Transform3D::transformed(
        const BasicVector3D<double>& v) const
{
    double x = m_matrix(0,0)*v.x() + m_matrix(0,1)*v.y() + m_matrix(0,2)*v.z();
    double y = m_matrix(1,0)*v.x() + m_matrix(1,1)*v.y() + m_matrix(1,2)*v.z();
    double z = m_matrix(2,0)*v.x() + m_matrix(2,1)*v.y() + m_matrix(2,2)*v.z();
    return Geometry::BasicVector3D<double>(x, y, z);
}

Geometry::BasicVector3D<complex_t> Geometry::Transform3D::transformed(
        const BasicVector3D<complex_t>& v) const
{
    complex_t x = m_matrix(0,0)*v.x() + m_matrix(0,1)*v.y() + m_matrix(0,2)*v.z();
    complex_t y = m_matrix(1,0)*v.x() + m_matrix(1,1)*v.y() + m_matrix(1,2)*v.z();
    complex_t z = m_matrix(2,0)*v.x() + m_matrix(2,1)*v.y() + m_matrix(2,2)*v.z();
    return Geometry::BasicVector3D<complex_t>(x, y, z);
}

Geometry::BasicVector3D<double> Geometry::Transform3D::transformedInverse(
        const BasicVector3D<double>& v) const
{
    double x = m_inverse_matrix(0,0)*v.x() + m_inverse_matrix(0,1)*v.y()
            + m_inverse_matrix(0,2)*v.z();
    double y = m_inverse_matrix(1,0)*v.x() + m_inverse_matrix(1,1)*v.y()
            + m_inverse_matrix(1,2)*v.z();
    double z = m_inverse_matrix(2,0)*v.x() + m_inverse_matrix(2,1)*v.y()
            + m_inverse_matrix(2,2)*v.z();
    return Geometry::BasicVector3D<double>(x, y, z);
}

Geometry::BasicVector3D<complex_t> Geometry::Transform3D::transformedInverse(
        const BasicVector3D<complex_t>& v) const
{
    complex_t x = m_inverse_matrix(0,0)*v.x() + m_inverse_matrix(0,1)*v.y()
            + m_inverse_matrix(0,2)*v.z();
    complex_t y = m_inverse_matrix(1,0)*v.x() + m_inverse_matrix(1,1)*v.y()
            + m_inverse_matrix(1,2)*v.z();
    complex_t z = m_inverse_matrix(2,0)*v.x() + m_inverse_matrix(2,1)*v.y()
            + m_inverse_matrix(2,2)*v.z();
    return Geometry::BasicVector3D<complex_t>(x, y, z);
}

Geometry::Transform3D* Geometry::Transform3D::clone() const
{
    return new Geometry::Transform3D(m_matrix);
}

Geometry::Transform3D Geometry::Transform3D::operator*(
        const Transform3D& other) const
{
    Eigen::Matrix3d product_matrix = this->m_matrix * other.m_matrix;
    return Geometry::Transform3D(product_matrix);
}

bool Geometry::Transform3D::operator==(const Geometry::Transform3D &other) const
{
    return this->m_matrix == other.m_matrix;
}

Geometry::Transform3D::ERotationType Geometry::Transform3D::getRotationType()
        const
{
    if (isXRotation()) return XAXIS;
    if (isYRotation()) return YAXIS;
    if (isZRotation()) return ZAXIS;
    return EULER;
}

bool Geometry::Transform3D::isIdentity() const
{
    double alpha, beta, gamma;
    calculateEulerAngles(&alpha, &beta, &gamma);
    return (alpha==0.0 && beta==0.0 && gamma==0.0);
}

void Geometry::Transform3D::print(std::ostream& ostr) const
{
    ostr << "Transform3D: " << m_matrix;
}

Geometry::Transform3D::Transform3D(const Eigen::Matrix3d& matrix)
: m_matrix(matrix)
{
    m_inverse_matrix = m_matrix.inverse();
}

bool Geometry::Transform3D::isXRotation() const
{
    if (m_matrix(0,0) != 1.0) return false;
    if (m_matrix(0,1) != 0.0) return false;
    if (m_matrix(0,2) != 0.0) return false;
    if (m_matrix(1,0) != 0.0) return false;
    if (m_matrix(2,0) != 0.0) return false;
    return true;
}

bool Geometry::Transform3D::isYRotation() const
{
    if (m_matrix(1,1) != 1.0) return false;
    if (m_matrix(0,1) != 0.0) return false;
    if (m_matrix(1,0) != 0.0) return false;
    if (m_matrix(1,2) != 0.0) return false;
    if (m_matrix(2,1) != 0.0) return false;
    return true;
}

bool Geometry::Transform3D::isZRotation() const
{
    if (m_matrix(2,2) != 1.0) return false;
    if (m_matrix(0,2) != 0.0) return false;
    if (m_matrix(1,2) != 0.0) return false;
    if (m_matrix(2,0) != 0.0) return false;
    if (m_matrix(2,1) != 0.0) return false;
    return true;
}

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file       Geometry/src/Transform3D.cpp
//! @brief      Implements template class Transform3D.
//!
//! @homepage   http://apps.jcns.fz-juelich.de/BornAgain
//! @license    GNU General Public License v3 or higher (see COPYING)
//! @copyright  Forschungszentrum Jülich GmbH 2013
//! @authors    C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Transform3D.h"

#include <Eigen/LU>


Geometry::Transform3D::Transform3D()
{
    m_matrix.setIdentity();
}

Geometry::Transform3D::Transform3D(const Transform3D& other)
: m_matrix(other.m_matrix)
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

Geometry::Transform3D* Geometry::Transform3D::createInverse() const
{
    Eigen::Matrix3d inverse = m_matrix.inverse();
    return new Transform3D(inverse);
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

Geometry::Transform3D* Geometry::Transform3D::clone() const
{
    return new Geometry::Transform3D(m_matrix);
}

Geometry::Transform3D Geometry::Transform3D::operator*(const Transform3D& other)
{
    Eigen::Matrix3d product_matrix = this->m_matrix * other.m_matrix;
    return Geometry::Transform3D(product_matrix);
}

void Geometry::Transform3D::print(std::ostream& ostr) const
{
    ostr << "Transform3D: " << m_matrix;
}

Geometry::Transform3D::Transform3D(const Eigen::Matrix3d& matrix)
: m_matrix(matrix)
{
}

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file       Geometry/inc/Transform3D.h
//! @brief      Defines class Transform3D.
//!
//!             Forked from CLHEP/Geometry, then heavily modified
//! @author     E. Chernyaev <Evgueni.Tcherniaev@cern.ch> 1996-2003
//!
//! @homepage   http://apps.jcns.fz-juelich.de/BornAgain
//! @license    GNU General Public License v3 or higher (see COPYING)
//! @copyright  Forschungszentrum Jülich GmbH 2013
//! @authors    C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//!
//
// ************************************************************************** //

#include <math.h>
#include <iostream>
#include "BasicVector3D.h"
#include "Transform3D.h"

typedef std::complex<double> complex_t;

namespace Geometry {

// -----------------------------------------------------------------------------
// Norm
// -----------------------------------------------------------------------------

//! Returns squared magnitude of the vector.
template<>
double BasicVector3D<double>::mag2() const
{
    return x()*x()+y()*y()+z()*z();
}

//! @TODO eliminate this, it is plain wrong
template<>
complex_t BasicVector3D<complex_t>::mag2() const
{
    return x()*x()+y()*y()+z()*z();
}

//! Returns magnitude of the vector.
template<>
double BasicVector3D<double>::mag() const
{
    return std::sqrt(mag2());
}

//! @TODO eliminate this, it is plain wrong
template<>
complex_t BasicVector3D<complex_t>::mag() const
{
    return std::sqrt(mag2());
}

// -----------------------------------------------------------------------------
// Cylindrical and spherical coordinate systems
// -----------------------------------------------------------------------------

//! Returns squared distance from z axis.
template<>
double BasicVector3D<double>::magxy2() const
{
    return x()*x()+y()*y();
}

//! @TODO eliminate this, it is plain wrong
template<>
complex_t BasicVector3D<complex_t>::magxy2() const
{
    return x()*x()+y()*y();
}

//! Returns distance from z axis.
template<>
double BasicVector3D<double>::magxy() const
{
    return std::sqrt(magxy2());
}

//! @TODO eliminate this, it is plain wrong
template<>
complex_t BasicVector3D<complex_t>::magxy() const
{
    return std::sqrt(magxy2());
}

//! Returns azimuth angle.
template<>
double BasicVector3D<double>::phi() const
{
    return x() == 0.0&& y() == 0.0 ? 0.0 : std::atan2(y(),x());
}

//! Returns polar angle.
template<>
double BasicVector3D<double>::theta() const
{
    return x() == 0.0&& y() == 0.0&& z() == 0.0 ?
        0.0 : std::atan2(magxy(),z());
}

//! Returns cosine of polar angle.
template<>
double BasicVector3D<double>::cosTheta() const
{
    double ma = mag();
    return std::abs(ma) == 0 ? 1 : z()/ma;
}

//! @TODO eliminate this, it is plain wrong
template<>
complex_t BasicVector3D<complex_t>::cosTheta() const
{
    complex_t ma = mag();
    return std::abs(ma) == 0 ? 1 : z()/ma;
}

//! Scale to given magnitude.
template<class T>
void BasicVector3D<T>::setMag(double ma)
{
    double factor = mag();
    if (factor > 0.0) {
        factor = ma/factor;
        v_[0] *= factor; v_[1] *= factor; v_[2] *= factor;
    }
}

// -----------------------------------------------------------------------------
// Combine two vectors
// -----------------------------------------------------------------------------

//! @TODO check usage: unlikely to be correct
template<>
BasicVector3D<complex_t> BasicVector3D<complex_t>::cross(
    const BasicVector3D<complex_t>& v) const
{
    return BasicVector3D<complex_t>(y()*v.z()-v.y()*z(),
                                 z()*v.x()-v.z()*x(),
                                 x()*v.y()-v.x()*y());
}

//! Returns square of transverse component with respect to given axis.
template<>
double BasicVector3D<double>::perp2(const BasicVector3D<double>& v) const
{
    double tot = v.mag2(), s = dot(v);
    return tot > 0.0 ? mag2()-s*s/tot : mag2();
}

//! Returns angle with respect to another vector.
template<>
double BasicVector3D<double>::angle(const BasicVector3D<double>& v) const
{
    double cosa = 0;
    double ptot = mag()*v.mag();
    if(ptot > 0) {
        cosa = dot(v)/ptot;
        if(cosa >  1) cosa =  1;
        if(cosa < -1) cosa = -1;
    }
    return std::acos(cosa);
}

// ----------------------------------------------------------------------------
// Rotations
// ----------------------------------------------------------------------------

template<class T>
BasicVector3D<T>& BasicVector3D<T>::rotateX (double a)
{
    double sina = std::sin(a);
    double cosa = std::cos(a);
    return BasicVector3D(
        x(),
        setY(y()*cosa-z()*sina),
        setZ(z()*cosa+y()*sina));
}

template<class T>
BasicVector3D<T>& BasicVector3D<T>::rotateY (double a)
{
    double sina = std::sin(a);
    double cosa = std::cos(a);
    return BasicVector3D(
        setX(x()*cosa+z()*sina),
        y(),
        setZ(z()*cosa-x()*sina));
}

template<class T>
BasicVector3D<T>& BasicVector3D<T>::rotateZ (double a)
{
    double sina = std::sin(a);
    double cosa = std::cos(a);
    return BasicVector3D(
        setX(x()*cosa-y()*sina),
        setY(y()*cosa+x()*sina),
        z());
}

template<>
BasicVector3D<double>& BasicVector3D<double>::rotate (
        double a, const BasicVector3D<double>& v)
{
    if (a  == 0) return *this;
    double cx = v.x(), cy = v.y(), cz = v.z();
    double ll = std::sqrt(cx*cx + cy*cy + cz*cz);
    if (ll == 0) {
        std::cerr << "BasicVector<double>::rotate() : zero axis" << std::endl;
        return *this;
    }
    double cosa = std::cos(a), sina = std::sin(a);
    cx /= ll; cy /= ll; cz /= ll;

    double xx = (1-cosa)*cx*cx + cosa;
    double xy = (1-cosa)*cx*cy - sina*cz;
    double xz = (1-cosa)*cx*cz + sina*cy;

    double yx = (1-cosa)*cy*cx + sina*cz;
    double yy = (1-cosa)*cy*cy + cosa;
    double yz = (1-cosa)*cy*cz - sina*cx;

    double zx = (1-cosa)*cz*cx - sina*cy;
    double zy = (1-cosa)*cz*cy + sina*cx;
    double zz = (1-cosa)*cz*cz + cosa;

    setXYZ(xx*x()+xy*y()+xz*z(),
           yx*x()+yy*y()+yz*z(),
           zx*x()+zy*y()+zz*z());
    return *this;
}

// =============================================================================
// Non-member functions for BasicVector3D<double>
// =============================================================================

// -----------------------------------------------------------------------------
// Transforms
// -----------------------------------------------------------------------------

template<>
BasicVector3D<double>& BasicVector3D<double>::transform(const Transform3D& m)
{
    setXYZ(m.xx()*x() + m.xy()*y() + m.xz()*z(),
           m.yx()*x() + m.yy()*y() + m.yz()*z(),
           m.zx()*x() + m.zy()*y() + m.zz()*z());
    return *this;
}

template<>
BasicVector3D<complex_t>& BasicVector3D<complex_t>::transform(const Transform3D& m)
{
    setXYZ(m.xx()*x() + m.xy()*y() + m.xz()*z(),
           m.yx()*x() + m.yy()*y() + m.yz()*z(),
           m.zx()*x() + m.zy()*y() + m.zz()*z());
    return *this;
}

}  // namespace Geometry

// ************************************************************************** //
//
//  heinzlibs:  Library collection of the Scientific Computing Group at
//              Heinz Maier-Leibnitz Zentrum (MLZ) Garching
//
//  libgeo3d:   Library for three-dimensional Euclidian geometry,
//              based on CLHEP/Geometry 1.9 of 1.4.2003,
//              forked after v 1.5 2010/06/16 16:21:27,
//
//! @file       Geometry/src/BasicVector3D.cpp
//! @brief      implements some methods of BasicVector3D<T> for T=double,complex
//!
//! @homepage   http://apps.jcns.fz-juelich.de/BornAgain
//! @license    GNU General Public License v3 or higher (see COPYING)
//! @copyright  Forschungszentrum Jülich GmbH 2013
//! @authors    E. Chernyaev <Evgueni.Tcherniaev@cern.ch> 1996-2003
//! @authors    C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//!
//! Changes w.r.t. CLHEP:
//! - eliminated support for type float
//! - eliminated support for istream
//! - added support for type complex<double> (but certain methods make no sense)
//! - reworked doxygen comments
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

template<>
BasicVector3D<double>& BasicVector3D<double>::rotateX (double a)
{
    double sina = std::sin(a);
    double cosa = std::cos(a);
    setY(y()*cosa-z()*sina);
    setZ(z()*cosa+y()*sina);
    return *this;
}

template<>
BasicVector3D<double>& BasicVector3D<double>::rotateY (double a)
{
    double sina = std::sin(a);
    double cosa = std::cos(a);
    setZ(z()*cosa-x()*sina);
    setX(x()*cosa+z()*sina);
    return *this;
}

template<>
BasicVector3D<double>& BasicVector3D<double>::rotateZ (double a)
{
    double sina = std::sin(a);
    double cosa = std::cos(a);
    setX(x()*cosa-y()*sina);
    setY(y()*cosa+x()*sina);
    return *this;
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

    double xx = cosa + (1-cosa)*cx*cx;
    double xy =        (1-cosa)*cx*cy - sina*cz;
    double xz =        (1-cosa)*cx*cz + sina*cy;

    double yx =        (1-cosa)*cy*cx + sina*cz;
    double yy = cosa + (1-cosa)*cy*cy;
    double yz =        (1-cosa)*cy*cz - sina*cx;

    double zx =        (1-cosa)*cz*cx - sina*cy;
    double zy =        (1-cosa)*cz*cy + sina*cx;
    double zz = cosa + (1-cosa)*cz*cz;

    cx = x(); cy = y(); cz = z();
    setXYZ(xx*cx+xy*cy+xz*cz, yx*cx+yy*cy+yz*cz, zx*cx+zy*cy+zz*cz);
    return *this;
}

// =============================================================================
// Non-member functions for BasicVector3D<double>
// =============================================================================

// -----------------------------------------------------------------------------
// Transforms
// -----------------------------------------------------------------------------

template<class T>
BasicVector3D<T>& BasicVector3D<T>::transform(const Transform3D& m)
{
    setXYZ(m.xx()*x() + m.xy()*y() + m.xz()*z(),
           m.yx()*x() + m.yy()*y() + m.yz()*z(),
           m.zx()*x() + m.zy()*y() + m.zz()*z());
    return *this;
}

}  // namespace Geometry

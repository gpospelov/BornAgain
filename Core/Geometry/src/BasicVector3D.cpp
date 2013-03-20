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
//! - added support for type complex<double>
//! - reworked doxygen comments
//
// ************************************************************************** //

#include <math.h>
#include <iostream>
#include "BasicVector3D.h"
#include "Transform3D.h"

typedef std::complex<double> complex_t;

namespace Geometry {

template<>
double BasicVector3D<double>::angle (const BasicVector3D<double>& v) const
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

template<>
BasicVector3D<double>& BasicVector3D<double>::rotateX (double a)
{
    double sina = std::sin(a), cosa = std::cos(a), dy = y(), dz = z();
    setY(dy*cosa-dz*sina);
    setZ(dz*cosa+dy*sina);
    return *this;
}

template<>
BasicVector3D<double>& BasicVector3D<double>::rotateY (double a)
{
    double sina = std::sin(a), cosa = std::cos(a), dz = z(), dx = x();
    setZ(dz*cosa-dx*sina);
    setX(dx*cosa+dz*sina);
    return *this;
}

template<>
BasicVector3D<double>& BasicVector3D<double>::rotateZ (double a)
{
    double sina = std::sin(a), cosa = std::cos(a), dx = x(), dy = y();
    setX(dx*cosa-dy*sina);
    setY(dy*cosa+dx*sina);
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

std::ostream& operator<< (
        std::ostream& os, const BasicVector3D<double>& a)
{
    return os << "(" << a.x() << "," << a.y() << "," << a.z() << ")";
}

std::ostream& operator<< (
        std::ostream& os, const BasicVector3D<complex_t>& a)
{
    return os << "(" << a.x() << "," << a.y() << "," << a.z() << ")";
}

template<>
BasicVector3D<double>& BasicVector3D<double>::transform (
            const Transform3D& m)
{
    double vx = x(), vy = y(), vz = z();
    setXYZ(m.xx()*vx + m.xy()*vy + m.xz()*vz,
           m.yx()*vx + m.yy()*vy + m.yz()*vz,
           m.zx()*vx + m.zy()*vy + m.zz()*vz);
    return *this;
}

template<>
BasicVector3D<complex_t>& BasicVector3D<complex_t>::transform (
            const Transform3D & m)
{
    complex_t vx = x(), vy = y(), vz = z();
    setXYZ(m.xx()*vx + m.xy()*vy + m.xz()*vz,
           m.yx()*vx + m.yy()*vy + m.yz()*vz,
           m.zx()*vx + m.zy()*vy + m.zz()*vz);
    return *this;
}

BasicVector3D<double> operator* (
            const Transform3D& m, const BasicVector3D<double>& v)
{
    double vx = v.x(), vy = v.y(), vz = v.z();
    return BasicVector3D<double>
            (m.xx()*vx + m.xy()*vy + m.xz()*vz,
             m.yx()*vx + m.yy()*vy + m.yz()*vz,
             m.zx()*vx + m.zy()*vy + m.zz()*vz);
}

}  // namespace Geometry

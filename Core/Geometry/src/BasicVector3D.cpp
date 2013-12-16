// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file       Geometry/src/BasicVector3D.cpp
//! @brief      Implements template class BasicVector3D.
//!
//! Using code from CLHEP/Geometry by E. Chernyaev, see BasicVector3D.h.
//!
//! @homepage   http://apps.jcns.fz-juelich.de/BornAgain
//! @license    GNU General Public License v3 or higher (see COPYING)
//! @copyright  Forschungszentrum Jülich GmbH 2013
//! @authors    C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include <math.h>
#include <iostream>
#include "BasicVector3D.h"

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

//! Returns squared magnitude of the vector.
template<>
complex_t BasicVector3D<complex_t>::mag2() const
{
    return std::conj(x())*x()+std::conj(y())*y()+std::conj(z())*z();
}

//! Returns magnitude of the vector.
template<>
double BasicVector3D<double>::mag() const
{
    return std::sqrt(mag2());
}

//! Returns magnitude of the vector.
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

//! Returns squared distance from z axis.
template<>
complex_t BasicVector3D<complex_t>::magxy2() const
{
    return std::conj(x())*x()+std::conj(y())*y();
}

//! Returns distance from z axis.
template<>
double BasicVector3D<double>::magxy() const
{
    return std::sqrt(magxy2());
}

//! Returns distance from z axis.
template<>
complex_t BasicVector3D<complex_t>::magxy() const
{
    return std::sqrt(magxy2());
}

//! Returns azimuth angle.
template<>
double BasicVector3D<double>::phi() const
{
    return x() == 0.0 && y() == 0.0 ? 0.0 : std::atan2(y(),x());
}

//! Returns polar angle.
template<>
double BasicVector3D<double>::theta() const
{
    return x() == 0.0 && y() == 0.0&& z() == 0.0 ?
        0.0 : std::atan2(magxy(),z());
}

//! Returns cosine of polar angle.
template<>
double BasicVector3D<double>::cosTheta() const
{
    double ma = mag();
    return std::abs(ma) == 0 ? 1 : z()/ma;
}

// -----------------------------------------------------------------------------
// Combine two vectors
// -----------------------------------------------------------------------------
//! Returns dot product of vectors
template<>
complex_t BasicVector3D<complex_t>::dot(const BasicVector3D<complex_t>& v) const
{
  // return x()*std::conj(v.x())+y()*std::conj(v.y())+z()*std::conj(v.z());
     return std::conj(x())*v.x()+std::conj(y())*v.y()+std::conj(z())*v.z();
}

template<>
double BasicVector3D<double>::dot(const BasicVector3D<double>& v) const
{
   return x()*v.x()+y()*v.y()+z()*v.z();
}

 //! Returns cross product of vectors
template<>
BasicVector3D<double> BasicVector3D<double>::cross(
    const BasicVector3D<double>& v) const
{
    return BasicVector3D<double>(y()*v.z()-v.y()*z(),
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

}  // namespace Geometry



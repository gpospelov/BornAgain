// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file       Geometry/src/BasicVector3D.cpp
//! @brief      Implements template class BasicVector3D.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include <iostream>
#include "BasicVector3D.h"

using std::conj;
using std::sqrt;
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
    return conj(x())*x()+conj(y())*y()+conj(z())*z();
}

//! Returns magnitude of the vector.
template<>
double BasicVector3D<double>::mag() const
{
    return sqrt(mag2());
}

//! Returns magnitude of the vector.
template<>
complex_t BasicVector3D<complex_t>::mag() const
{
    return sqrt(mag2());
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
    return conj(x())*x()+conj(y())*y();
}

//! Returns distance from z axis.
template<>
double BasicVector3D<double>::magxy() const
{
    return sqrt(magxy2());
}

//! Returns distance from z axis.
template<>
complex_t BasicVector3D<complex_t>::magxy() const
{
    return sqrt(magxy2());
}

//! Returns azimuth angle.
template<>
double BasicVector3D<double>::phi() const
{
    return x() == 0.0 && y() == 0.0 ? 0.0 : std::atan2(-y(),x());
}

//! Returns polar angle.
template<>
double BasicVector3D<double>::theta() const
{
    return x() == 0.0 && y() == 0.0 && z() == 0.0 ?
        0.0 : std::atan2(magxy(),z());
}

//! Returns cosine of polar angle.
template<>
double BasicVector3D<double>::cosTheta() const
{
    return mag() == 0 ? 1 : z()/mag();
}

//! Returns squared sine of polar angle.
template<>
double BasicVector3D<double>::sin2Theta() const
{
    return mag2() == 0 ? 0 : magxy2()/mag2();
}

//! Returns this, trivially converted to complex type.
template<>
BasicVector3D<std::complex<double>> BasicVector3D<double>::complex() const
{
    return BasicVector3D<std::complex<double>>( v_[0], v_[1], v_[2] );
}


// -----------------------------------------------------------------------------
// Combine two vectors
// -----------------------------------------------------------------------------

//! Returns dot product of vectors (antilinear in the first [=self] argument).
template<>
complex_t BasicVector3D<complex_t>::dot(const BasicVector3D<complex_t>& v) const
{
     return conj(x())*v.x()+conj(y())*v.y()+conj(z())*v.z();
}

template<>
double BasicVector3D<double>::dot(const BasicVector3D<double>& v) const
{
   return x()*v.x()+y()*v.y()+z()*v.z();
}

 //! Returns cross product of vectors.
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

BasicVector3D<std::complex<double> > toComplexVector(const BasicVector3D<double> &real_vector)
{
    return BasicVector3D<std::complex<double> >(complex_t(real_vector.x()),
                                                complex_t(real_vector.y()),
                                                complex_t(real_vector.z()));
}

// -----------------------------------------------------------------------------
// Quasi constructor
// -----------------------------------------------------------------------------

BasicVector3D<double> vecOfLambdaAlphaPhi(const double _lambda, const double _alpha, const double _phi)
{
    double k = PI2/_lambda;
    return BasicVector3D<double>(
        k*std::cos(_alpha) * std::cos(_phi),
        -k*std::cos(_alpha) * std::sin(_phi),
        k*std::sin(_alpha) );
}

}  // namespace Geometry

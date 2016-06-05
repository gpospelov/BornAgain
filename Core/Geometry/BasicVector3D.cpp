// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file       Geometry/BasicVector3D.cpp
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

typedef std::complex<double> complex_t;

namespace Geometry {

// -----------------------------------------------------------------------------
// Functions of this (with no further argument)
// -----------------------------------------------------------------------------

//! Returns complex conjugate vector
template<>
BasicVector3D<double> BasicVector3D<double>::conj() const
{
    return *this;
}

//! Returns complex conjugate vector
template<>
BasicVector3D<complex_t > BasicVector3D<complex_t >::conj() const
{
    return BasicVector3D<complex_t >(std::conj(v_[0]), std::conj(v_[1]), std::conj(v_[2]));
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

//! Returns dot product of complex vectors (antilinear in the first [=self] argument).
template<> template<>
complex_t BasicVector3D<complex_t>::dot(const BasicVector3D<complex_t>& v) const
{
     return std::conj(x())*v.x()+std::conj(y())*v.y()+std::conj(z())*v.z();
}

//! Returns mixed dot product of complex and double vectors (antilinear in the complex argument).
template<> template<>
complex_t BasicVector3D<complex_t>::dot(const BasicVector3D<double>& v) const
{
     return std::conj( x()*v.x()+y()*v.y()+z()*v.z() );
}

//! Returns mixed dot product of double and complex vectors (linear in the complex argument).
template<> template<>
complex_t BasicVector3D<double>::dot(const BasicVector3D<complex_t>& v) const
{
     return x()*v.x()+y()*v.y()+z()*v.z();
}

//! Returns dot product of double-typed vectors.
template<> template<>
double BasicVector3D<double>::dot(const BasicVector3D<double>& v) const
{
   return x()*v.x()+y()*v.y()+z()*v.z();
}

 //! Returns cross product of double-typed vectors.
template<> template<>
BasicVector3D<double> BasicVector3D<double>::cross(const BasicVector3D<double>& v) const
{
    return BasicVector3D<double>(y()*v.z()-v.y()*z(),
                                 z()*v.x()-v.z()*x(),
                                 x()*v.y()-v.x()*y());
}

 //! Returns mixed cross product of double and complex vectors.
template<> template<>
BasicVector3D<complex_t> BasicVector3D<double>::cross(const BasicVector3D<complex_t>& v) const
{
    return BasicVector3D<complex_t>(y()*v.z()-v.y()*z(),
                                    z()*v.x()-v.z()*x(),
                                    x()*v.y()-v.x()*y());
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

BasicVector3D<double> vecOfLambdaAlphaPhi(
    const double _lambda, const double _alpha, const double _phi)
{
    double k = PI2/_lambda;
    return BasicVector3D<double>(
        k*std::cos(_alpha) * std::cos(_phi),
        -k*std::cos(_alpha) * std::sin(_phi),
        k*std::sin(_alpha) );
}

}  // namespace Geometry

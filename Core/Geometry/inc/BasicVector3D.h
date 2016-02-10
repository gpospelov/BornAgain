// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file       Geometry/inc/BasicVector3D.h
//! @brief      Defines template class BasicVector3D.
//!
//! Forked from CLHEP/Geometry by E. Chernyaev <Evgueni.Tcherniaev@cern.ch>,
//! then reduced to rotations and mostly rewritten; point and vector semantics
//! is no longer represented by class type; transforms are no longer methods of
//! BasicVector3D; there is a new class Transform3D.
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef GEOMETRY_BASICVECTOR3D_H
#define GEOMETRY_BASICVECTOR3D_H

static const double PI2 = 6.28318530717958647692528676655900577;
#include "WinDllMacros.h"
#include <complex>

namespace Geometry {

//! @class BasicVector3D
//! @ingroup tools_internal
//! @brief Base class for Point3D<T>, Vector3D<T> and Normal3D<T>.
//!
//! It defines only common functionality for those classes and
//! should not be used as separate class.
//!
//! @author Evgeni Chernyaev 1996-2003

template<class T>
class BasicVector3D {
protected:
    T v_[3];

public:
    //! Default constructor.
    //! It is protected - this class should not be instantiated directly.
    BasicVector3D()
    { v_[0] = 0.0; v_[1] = 0.0; v_[2] = 0.0; }

    //! Constructor from three numbers.
    BasicVector3D(const T x1, const T y1, const T z1)
    { v_[0] = x1; v_[1] = y1; v_[2] = z1; }

    //! Destructor.
    ~BasicVector3D() {}

    // -----------------------------
    // General arithmetic operations
    // -----------------------------

    //! Assignment.
    inline BasicVector3D<T>& operator= (const BasicVector3D<T>& v)
    { v_[0] = v.v_[0]; v_[1] = v.v_[1]; v_[2] = v.v_[2]; return *this; }

    //! Addition.
    inline BasicVector3D<T>& operator+=(const BasicVector3D<T>& v)
    { v_[0] += v.v_[0]; v_[1] += v.v_[1]; v_[2] += v.v_[2]; return *this; }

    //! Subtraction.
    inline BasicVector3D<T>& operator-=(const BasicVector3D<T>& v)
    { v_[0] -= v.v_[0]; v_[1] -= v.v_[1]; v_[2] -= v.v_[2]; return *this; }

    //! Multiplication by scalar.
    inline BasicVector3D<T>& operator*=(double a)
    { v_[0] *= a; v_[1] *= a; v_[2] *= a; return *this; }

    //! Division by scalar.
    inline BasicVector3D<T>& operator/=(double a)
    { v_[0] /= a; v_[1] /= a; v_[2] /= a; return *this; }

    // ------------
    // Subscripting
    // ------------

    //! Returns components by index.
    inline T operator[](int i) const { return v_[i]; }

    //! Sets components by index.
    inline T& operator[](int i) { return v_[i]; }

    // ------------------------------------
    // Cartesian coordinate system: x, y, z
    // ------------------------------------

    //! Returns x-component in cartesian coordinate system.
    inline T x() const { return v_[0]; }
    //! Returns y-component in cartesian coordinate system.
    inline T y() const { return v_[1]; }
    //! Returns z-component in cartesian coordinate system.
    inline T z() const { return v_[2]; }

    //! Sets x-component in cartesian coordinate system.
    inline void setX(const T&a) { v_[0] = a; }
    //! Sets y-component in cartesian coordinate system.
    inline void setY(const T&a) { v_[1] = a; }
    //! Sets z-component in cartesian coordinate system.
    inline void setZ(const T&a) { v_[2] = a; }

    //! Sets components in cartesian coordinate system.
    inline void setXYZ(const T&x1, const T&y1, const T&z1)
    { v_[0] = x1; v_[1] = y1; v_[2] = z1; }

    // ----
    // Norm
    // ----

    //! Returns squared magnitude squared of the vector.
    T mag2() const;

    //! Returns magnitude of the vector.
    T mag() const;

    // --------------------------------------------
    // Cylindrical and spherical coordinate systems
    // --------------------------------------------

    //! Returns squared distance from z axis.
    T magxy2() const;

    //! Returns distance from z axis.
    T magxy() const;

    //! Returns azimuth angle.
    double phi() const;

    //! Returns polar angle.
    double theta() const;

    //! Returns cosine of polar angle.
    double cosTheta() const;

    //! Returns squared sine of polar angle.
    double sin2Theta() const;

    // -------------------
    // Combine two vectors
    // -------------------

    //! Returns dot product of vectors (antilinear in the first [=self] argument).
    T dot(const BasicVector3D<T>& v) const;

    //! Returns cross product of vectors.
    BasicVector3D<T> cross(const BasicVector3D<T>& v ) const;

    //! Returns normalized vector
    BasicVector3D<T> normalize() const;

    //! Returns square of transverse component with respect to given axis.
    double perp2(const BasicVector3D<T>& v) const;

    //! Returns transverse component with respect to given axis.
    inline T perp(const BasicVector3D<T>& v) const
    { return std::sqrt(perp2(v)); }

    //! Returns angle with respect to another vector.
    double angle(const BasicVector3D<T>& v) const;

    // ---------
    // Rotations
    // ---------

    //! Returns result of rotation around x-axis.
    BasicVector3D<T> rotatedX(double a) const;
    //! Returns result of rotation around y-axis.
    BasicVector3D<T> rotatedY(double a) const;
    //! Returns result of rotation around z-axis.
    BasicVector3D<T> rotatedZ(double a) const;
    //! Returns result of rotation around the axis specified by another vector.
    BasicVector3D<T> rotated(double a, const BasicVector3D<T>& v) const;

    // ---------------
    // Related vectors
    // ---------------

    //! Returns unit vector in direction of this (or null vector).
    inline BasicVector3D<T> unit() const {
        double len = mag();
        return (len > 0.0) ?
            BasicVector3D<T>(x()/len, y()/len, z()/len) :
            BasicVector3D<T>();
    }

    // ---------------------------------------------
    // Specifically for grazing-incidence scattering
    // ---------------------------------------------

    //! Sets wave vector for given wavelength and angles/
    inline void setLambdaAlphaPhi(
        const T& _lambda, const T& _alpha, const T& _phi)
        {
            T k = PI2/_lambda;
            v_[0] = k*std::cos(_alpha) * std::cos(_phi);
            v_[1] = -k*std::cos(_alpha) * std::sin(_phi);
            v_[2] = k*std::sin(_alpha);
        }
};

// =========================================================================
// Non-member functions for BasicVector3D<T>
// =========================================================================

//! Output to stream.
//! @relates BasicVector3D
template <class T>
std::ostream&
operator<<(std::ostream& os, const BasicVector3D<T>& a)
{ return os << "(" << a.x() << "," << a.y() << "," << a.z() << ")"; }

// -----------------
// Scalar operations
// -----------------

//! Unary plus.
//! @relates BasicVector3D
template <class T>
inline BasicVector3D<T>
operator+(const BasicVector3D<T>& v)
{ return v; }

//! Unary minus.
//! @relates BasicVector3D
template <class T>
inline BasicVector3D<T>
operator-(const BasicVector3D<T>& v)
{ return BasicVector3D<T>(-v.x(), -v.y(), -v.z()); }

//! Multiplication vector by scalar.
//! @relates BasicVector3D
template <class T, class U>
inline BasicVector3D<T>
operator*(const BasicVector3D<T>& v, U a)
{ return BasicVector3D<T>(v.x()*a, v.y()*a, v.z()*a); }

//! Multiplication scalar by vector.
//! @relates BasicVector3D
template <class T, class U>
inline BasicVector3D<T>
operator*(U a, const BasicVector3D<T>& v)
{ return BasicVector3D<T>(a*v.x(), a*v.y(), a*v.z()); }

//! Division vector by scalar.
//! @relates BasicVector3D
template <class T, class U>
inline BasicVector3D<T>
operator/(const BasicVector3D<T>& v, U a)
{ return BasicVector3D<T>(v.x()/a, v.y()/a, v.z()/a); }

// -----------------------------------
// Operations involving another vector
// -----------------------------------

//! Addition of two vectors.
//! @relates BasicVector3D
template <class T>
inline BasicVector3D<T>
operator+(const BasicVector3D<T>& a,const BasicVector3D<T>& b)
{ return BasicVector3D<T>(a.x()+b.x(), a.y()+b.y(), a.z()+b.z()); }

//! Subtraction of two vectors.
//! @relates BasicVector3D
template <class T>
inline BasicVector3D<T>
operator-(const BasicVector3D<T>& a,const BasicVector3D<T>& b)
{ return BasicVector3D<T>(a.x()-b.x(), a.y()-b.y(), a.z()-b.z()); }

//! Scalar product of two vectors.

//! @relates BasicVector3D
//! We do not provide the operator form a*b:
//! Though nice to write, and in some cases perfectly justified,
//! in general it tends to make expressions more difficult to read.
template <class T>
inline T
dotProduct(const BasicVector3D<T>& a, const BasicVector3D<T>& b)
{ return a.dot(b); }

//! Cross product.
//! @relates BasicVector3D
template <class T>
inline BasicVector3D<T>
crossProduct(const BasicVector3D<T>& a, const BasicVector3D<T>& b)
{ return a.cross(b); }

//! Comparison of two vectors for equality.
//! @relates BasicVector3D
template <class T>
inline bool
operator==(const BasicVector3D<T>& a, const BasicVector3D<T>& b)
{ return (a.x()==b.x()&& a.y()==b.y()&& a.z()==b.z()); }

//! Comparison of two vectors for inequality.
//! @relates BasicVector3D
template <class T>
inline bool
operator!=(const BasicVector3D<T>& a, const BasicVector3D<T>& b)
{ return (a.x()!=b.x() || a.y()!=b.y() || a.z()!=b.z()); }

template<> BA_CORE_API_ double BasicVector3D<double>::mag2() const;

template<> BA_CORE_API_ double BasicVector3D<double>::mag() const;

template<> BA_CORE_API_ double BasicVector3D<double>::magxy2() const;

template<> BA_CORE_API_ double BasicVector3D<double>::magxy() const;

template<> BA_CORE_API_ std::complex<double>
        BasicVector3D<std::complex<double> >::magxy() const;

template<> BA_CORE_API_ std::complex<double> BasicVector3D<std::complex<double> >::dot(
        const BasicVector3D<std::complex<double> >& v) const;

template<> BA_CORE_API_ double BasicVector3D<double>::dot(
        const BasicVector3D<double>& v) const;

template<> BA_CORE_API_ BasicVector3D<double> BasicVector3D<double>::cross(
        const BasicVector3D<double>& v) const;

template<> BA_CORE_API_ double BasicVector3D<double>::phi() const;

template<> BA_CORE_API_ double BasicVector3D<double>::theta() const;

BA_CORE_API_ BasicVector3D<std::complex<double> > toComplexVector(
        const BasicVector3D<double>& real_vector);

}  // namespace Geometry

#endif /* GEOMETRY_BASICVECTOR3D_H */

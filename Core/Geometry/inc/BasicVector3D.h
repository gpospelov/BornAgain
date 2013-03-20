// ************************************************************************** //
//
//  heinzlibs:  Library collection of the Scientific Computing Group at
//              Heinz Maier-Leibnitz Zentrum (MLZ) Garching
//
//  libgeo3d:   Library for three-dimensional Euclidian geometry,
//              based on CLHEP/Geometry 1.9 of 1.4.2003,
//              forked after v 1.5 2010/06/16 16:21:27,
//
//! @file       Geometry/inc/BasicVector3D.h
//! @brief      defines class BasicVector<T> for T=double,complex,
//!               and implements most functions
//!
//! @homepage   http://apps.jcns.fz-juelich.de/BornAgain
//! @license    GNU General Public License v3 or higher (see COPYING)
//! @copyright  Forschungszentrum Jülich GmbH 2013
//! @authors    E. Chernyaev <Evgueni.Tcherniaev@cern.ch> 1996-2003
//! @authors    C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//!
//! Changes w.r.t. CLHEP:
//! - eliminated support for type float
//! - added support for type complex<double>
//! - added some new methods
//! - reworked doxygen comments
//
// ************************************************************************** //

#ifndef GEOMETRY_BASICVECTOR3D_H
#define GEOMETRY_BASICVECTOR3D_H

#include <cmath>
#include <complex>
#include "Exceptions.h"

namespace Geometry {

class Transform3D;

//! Base class for Point3D<T>, Vector3D<T> and Normal3D<T>.

//! It defines only common functionality for those classes and
//! should not be used as separate class.
//!
//! @author Evgeni Chernyaev 1996-2003
//!
template<class T> class BasicVector3D {
  protected:
    T v_[3];
    
  public:
    //! Default constructor.
    //! It is protected - this class should not be instantiated directly.
    BasicVector3D() { v_[0] = 0.0; v_[1] = 0.0; v_[2] = 0.0; }

    //! Safe indexing of coordinates, for matrices, arrays, etc.
    enum {
        X = 0,                  //!< index for x-component
        Y = 1,                  //!< index for y-component
        Z = 2,                  //!< index for z-component
        NUM_COORDINATES = 3,    //!< number of components
        SIZE = NUM_COORDINATES  //!< number of components
    };

    //! Constructor from three numbers.
    BasicVector3D(const T&x1, const T&y1, const T&z1) {
        v_[0] = x1; v_[1] = y1; v_[2] = z1; }

    //! Destructor.
    virtual ~BasicVector3D() {}

    // -----------------------------
    // General arithmetic operations
    // -----------------------------

    //! Assignment.
    inline BasicVector3D<T>& operator= (const BasicVector3D<T>& v) {
        v_[0] = v.v_[0]; v_[1] = v.v_[1]; v_[2] = v.v_[2]; return *this;
    }
    //! Addition.
    inline BasicVector3D<T>& operator+=(const BasicVector3D<T>& v) {
        v_[0] += v.v_[0]; v_[1] += v.v_[1]; v_[2] += v.v_[2]; return *this;
    }
    //! Subtraction.
    inline BasicVector3D<T>& operator-=(const BasicVector3D<T>& v) {
        v_[0] -= v.v_[0]; v_[1] -= v.v_[1]; v_[2] -= v.v_[2]; return *this;
    }
    //! Multiplication by scalar.
    inline BasicVector3D<T>& operator*=(double a) {
        v_[0] *= a; v_[1] *= a; v_[2] *= a; return *this;
    }
    //! Division by scalar.
    inline BasicVector3D<T>& operator/=(double a) {
        v_[0] /= a; v_[1] /= a; v_[2] /= a; return *this;
    }

    // ------------
    // Subscripting
    // ------------

    //! Return components by index.
    inline T operator[](int i) const { return v_[i]; }

    //! Set components by index.
    inline T& operator[](int i) { return v_[i]; }

    // ------------------------------------
    // Cartesian coordinate system: x, y, z
    // ------------------------------------

    //! Return x-component in cartesian coordinate system.
    inline T x() const { return v_[0]; }
    //! Return y-component in cartesian coordinate system.
    inline T y() const { return v_[1]; }
    //! Return z-component in cartesian coordinate system.
    inline T z() const { return v_[2]; }

    //! Set x-component in cartesian coordinate system.
    inline void setX(const T&a) { v_[0] = a; }
    //! Set y-component in cartesian coordinate system.
    inline void setY(const T&a) { v_[1] = a; }
    //! Set z-component in cartesian coordinate system.
    inline void setZ(const T&a) { v_[2] = a; }

    //! Set components in cartesian coordinate system.
    inline void setXYZ(const T&x1, const T&y1, const T&z1) {
        v_[0] = x1; v_[1] = y1; v_[2] = z1; }

    // ----
    // Norm
    // ----

    //! Return squared magnitude squared of the vector.
    double mag2() const;

    //! Return magnitude of the vector.
    double mag() const;

    // --------------------------------------------
    // Cylindrical and spherical coordinate systems
    // --------------------------------------------

    //! Return squared distance from z axis.
    double magxy2() const;

    //! Return distance from z axis.
    double magxy() const;

    //! Return azimuth angle.
    double phi() const;

    //! Return polar angle.
    double theta() const;

    //! Return cosine of polar angle.
    double cosTheta() const;

    //! Scale to given magnitude.
    void setMag(double ma);

    // -------------------
    // Combine two vectors
    // -------------------

    //! Scalar product.
    double dot(const BasicVector3D<T>& v) const;

    //! Vector product.
    BasicVector3D<T> cross(const BasicVector3D<T>& v) const;

    //! Return square of transverse component with respect to given axis.
    double perp2(const BasicVector3D<T>& v) const;

    //! Return transverse component with respect to given axis.
    inline T perp(const BasicVector3D<T>& v) const {
        return std::sqrt(perp2(v));
    }

    //! Return angle with respect to another vector.
    T angle(const BasicVector3D<T>& v) const;

    // ---------------
    // Related vectors
    // ---------------

    //! Return unit vector parallel to this.
    inline BasicVector3D<T> unit() const {
        T len = mag();
        return (len > 0.0) ?
            BasicVector3D<T>(x()/len, y()/len, z()/len) :
            BasicVector3D<T>();
    }

    //! Return somewhat arbitrarily chosen orthogonal vector.
    BasicVector3D<T> orthogonal() const {
        T dx = x() < 0.0 ? -x() : x();
        T dy = y() < 0.0 ? -y() : y();
        T dz = z() < 0.0 ? -z() : z();
        if (dx < dy) {
            return dx < dz ?
                BasicVector3D<T>(0.0,z(),-y()) :
                BasicVector3D<T>(y(),-x(),0.0);
        } else {
            return dy < dz ?
                BasicVector3D<T>(-z(),0.0,x()) :
                BasicVector3D<T>(y(),-x(),0.0);
        }
    }

    // ---------
    // Rotations
    // ---------

    //! Rotates around x-axis.
    BasicVector3D<T>& rotateX(T a);
    //! Rotates around y-axis.
    BasicVector3D<T>& rotateY(T a);
    //! Rotates around z-axis.
    BasicVector3D<T>& rotateZ(T a);
    //! Rotates around the axis specified by another vector.
    BasicVector3D<T>& rotate(T a, const BasicVector3D<T>& v);

    // ---------------------------------------------
    // Specifically for grazing-incidence scattering
    // ---------------------------------------------

    //! Set wave vector for given wavelength and angles/
    inline void setLambdaAlphaPhi(
        const T&_lambda, const T&_alpha, const T&_phi)
        {
            T k = 2.*M_PI/_lambda;
            v_[0] = k*std::cos(_alpha) * std::cos(_phi);
            v_[1] = k*std::cos(_alpha) * std::sin(_phi);
            v_[2] = k*std::sin(_alpha);
        }

    //! Transformation by Transform3D, as function.
    //!
    //! This is an alternative to operator*(const Transform3D&,&T) below.
    BasicVector3D<T>&transform(const Transform3D&m);
};

// =========================================================================
// Non-member functions for BasicVector3D<double>
// =========================================================================

//! Output to stream.
//! @relates BasicVector3D
std::ostream&
operator<<(std::ostream&, const BasicVector3D<double>&);

// -----------------
// Scalar operations
// -----------------

//! Unary plus.
//! @relates BasicVector3D
inline BasicVector3D<double>
operator+(const BasicVector3D<double>& v) { return v; }

//! Unary minus.
//! @relates BasicVector3D
inline BasicVector3D<double>
operator-(const BasicVector3D<double>& v) {
    return BasicVector3D<double>(-v.x(), -v.y(), -v.z()); }

//! Multiplication vector by scalar.
//! @relates BasicVector3D
inline BasicVector3D<double>
operator*(const BasicVector3D<double>& v, double a) {
    return BasicVector3D<double>(v.x()*a, v.y()*a, v.z()*a); }

//! Multiplication scalar by vector.
//! @relates BasicVector3D
inline BasicVector3D<double>
operator*(double a, const BasicVector3D<double>& v) {
    return BasicVector3D<double>(a*v.x(), a*v.y(), a*v.z()); }

//! Division vector by scalar.
//! @relates BasicVector3D
inline BasicVector3D<double>
operator/(const BasicVector3D<double>& v, double a) {
    return BasicVector3D<double>(v.x()/a, v.y()/a, v.z()/a); }

// -----------------------------------
// Operations involving another vector
// -----------------------------------

//! Addition of two vectors.
//! @relates BasicVector3D
inline BasicVector3D<double>
operator+(const BasicVector3D<double>& a,const BasicVector3D<double>& b) {
    return BasicVector3D<double>(a.x()+b.x(), a.y()+b.y(), a.z()+b.z()); }

//! Subtraction of two vectors.
//! @relates BasicVector3D
inline BasicVector3D<double>
operator-(const BasicVector3D<double>& a,const BasicVector3D<double>& b) {
    return BasicVector3D<double>(a.x()-b.x(), a.y()-b.y(), a.z()-b.z());
}

//! Scalar product of two vectors, as operator.
//! @relates BasicVector3D
double operator*(const BasicVector3D<double>& a,
                 const BasicVector3D<double>& b);

//! Scalar product of two vectors, as function.
//! @relates BasicVector3D
inline double DotProduct(const BasicVector3D<double>&left,
                         const BasicVector3D<double>&right)
{
    return left.x()*right.x() + left.y()*right.y() + left.z()*right.z();
}

//! Cross product.
//! @relates BasicVector3D
inline BasicVector3D<double>
CrossProduct(const BasicVector3D<double>&left,
             const BasicVector3D<double>&right)
{
    double x = left.y()*right.z() - left.z()*right.y();
    double y = left.z()*right.x() - left.x()*right.z();
    double z = left.x()*right.y() - left.y()*right.x();
    return BasicVector3D<double> (x, y, z);
}

//! Comparison of two vectors for equality.
//! @relates BasicVector3D
inline bool
operator==(const BasicVector3D<double>& a, const BasicVector3D<double>& b)
    { return (a.x()==b.x()&& a.y()==b.y()&& a.z()==b.z()); }

//! Comparison of two vectors for inequality.
//! @relates BasicVector3D
inline bool
operator!=(const BasicVector3D<double>& a, const BasicVector3D<double>& b)
    { return (a.x()!=b.x() || a.y()!=b.y() || a.z()!=b.z()); }

// ----------
// Transforms
// ----------

//! Transformation of BasicVector3D<double> by Transform3D.
//! @relates BasicVector3D
BasicVector3D<double>
operator*(const Transform3D& m, const BasicVector3D<double>& v);

// =========================================================================
// Non-member functions for BasicVector3D<std::complex<double> >
// =========================================================================

//! Output to stream.
//! @relates BasicVector3D
std::ostream&
operator<<(std::ostream&, const BasicVector3D<std::complex<double> >&);

// -----------------
// Scalar operations
// -----------------

//! Unary plus.
//! @relates BasicVector3D
inline BasicVector3D<std::complex<double> >
operator+(const BasicVector3D<std::complex<double> >& v) { return v; }

//! Unary minus.
//! @relates BasicVector3D
inline BasicVector3D<std::complex<double> >
operator-(const BasicVector3D<std::complex<double> >& v) {
    return BasicVector3D<std::complex<double> >(-v.x(), -v.y(), -v.z());
}

//! Multiplication vector by scalar.
//! @relates BasicVector3D
inline BasicVector3D<std::complex<double> >
operator*(const BasicVector3D<const std::complex<double> >& v,
          const std::complex<double>&a) {
    return BasicVector3D<std::complex<double> >(v.x()*a, v.y()*a, v.z()*a);
}

//! Multiplication scalar by vector.
//! @relates BasicVector3D
inline BasicVector3D<std::complex<double> >
operator*(const std::complex<double>&a,
          const BasicVector3D<std::complex<double> >& v) {
    return BasicVector3D<std::complex<double> >(a*v.x(), a*v.y(), a*v.z());
}

//! Division vector by scalar.
//! @relates BasicVector3D
inline BasicVector3D<std::complex<double> >
operator/(const BasicVector3D<std::complex<double> >& v,
          const std::complex<double>&a) {
    return BasicVector3D<std::complex<double> >(v.x()/a, v.y()/a, v.z()/a);
}

// -----------------------------------
// Operations involving another vector
// -----------------------------------

//! Addition of two vectors.
//! @relates BasicVector3D
inline BasicVector3D<std::complex<double> >
operator+(const BasicVector3D<std::complex<double> >& a,
          const BasicVector3D<std::complex<double> >& b) {
    return BasicVector3D<std::complex<double> >(
        a.x()+b.x(), a.y()+b.y(), a.z()+b.z() );
}

//! Subtraction of two vectors.
//! @relates BasicVector3D
inline BasicVector3D<std::complex<double> >
operator-(const BasicVector3D<std::complex<double> >& a,
          const BasicVector3D<std::complex<double> >& b) {
    return BasicVector3D<std::complex<double> >(
        a.x()-b.x(), a.y()-b.y(), a.z()-b.z() );
}

//! Cross product.
//! @relates BasicVector3D
inline BasicVector3D<std::complex<double> >
CrossProduct(const BasicVector3D<std::complex<double> >&left,
             const BasicVector3D<std::complex<double> >&right)
{
    std::complex<double> x = left.y()*right.z() - left.z()*right.y();
    std::complex<double> y = left.z()*right.x() - left.x()*right.z();
    std::complex<double> z = left.x()*right.y() - left.y()*right.x();
    return BasicVector3D<std::complex<double> > (x, y, z);
}

//! Comparison of two vectors for equality.
//! @relates BasicVector3D
inline bool
operator==(const BasicVector3D<std::complex<double> >& a,
           const BasicVector3D<std::complex<double> >& b) {
    return (a.x()==b.x()&& a.y()==b.y()&& a.z()==b.z());
}

//! Comparison of two vectors for inequality.
//! @relates BasicVector3D
inline bool
operator!=(const BasicVector3D<std::complex<double> >& a,
           const BasicVector3D<std::complex<double> >& b) {
    return (a.x()!=b.x() || a.y()!=b.y() || a.z()!=b.z());
}

// ----------
// Transforms
// ----------

//! Transformation of BasicVector3D<double> by Transform3D.
//! @relates BasicVector3D
BasicVector3D<std::complex<double> >
operator*(const Transform3D& m,
          const BasicVector3D<std::complex<double> >& v);

}  // namespace Geometry

#endif /* GEOMETRY_BASICVECTOR3D_H */

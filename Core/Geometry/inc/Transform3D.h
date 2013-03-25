// ************************************************************************** //
//
//  heinzlibs:  Library collection of the Scientific Computing Group at
//              Heinz Maier-Leibnitz Zentrum (MLZ) Garching
//
//  libgeo3d:   Library for three-dimensional Euclidian geometry,
//              based on CLHEP/Geometry 1.9 of 1.4.2003,
//              forked after v 1.5 2010/06/16 16:21:27,
//
//! @file       Geometry/inc/Transform3D.h
//! @brief      defines class Transform3D,
//!               a 4x3 double-precision transformation matrix
//!
//! @homepage   http://apps.jcns.fz-juelich.de/BornAgain
//! @license    GNU General Public License v3 or higher (see COPYING)
//! @copyright  Forschungszentrum Jülich GmbH 2013
//! @authors    E. Chernyaev <Evgueni.Tcherniaev@cern.ch> 1996-2003
//! @authors    C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//!
//! Changes w.r.t. CLHEP:
//! - eliminated distinction vector/normal/point
//! - eliminated unused transforms
//! - reworked doxygen comments
//
// ************************************************************************** //

#ifndef GEOMETRY_TRANSFROM3D_H
#define GEOMETRY_TRANSFROM3D_H

#include <cmath>
#include "BasicVector3D.h"

// remnants of CLHEP:
#define Point3D  BasicVector3D
#define Vector3D BasicVector3D
#define Normal3D BasicVector3D

namespace Geometry {

// ************************************************************************** //
//  Main class Transform3D
// ************************************************************************** //

//! Transformations of 3D geometrical objects (points, vectors, normals).

//! Uses a 3x3 double-precision transform matrix to rotate vectors.
//!
//! Identity transformation:
//!   Transform3D::Identity   - global identity transformation;
//!   any constructor without parameters, e.g. Transform3D();
//!   m.setIdentity()            - set "m" to identity;
//!
//! General transformations:
//!   Transform3D(m,v)         - transformation given by Rotation "m"
//!                              and CLHEP::Hep3Vector "v";
//!   Transform3D(a0,a1,a2, b0,b1,b2) - transformation given by initial
//!                               and transformed positions of three points;
//! Rotations:
//!   Rotate3D(m)              - rotation given by CLHEP::HepRotation "m";
//!   Rotate3D(ang,v)          - rotation through the angle "ang" around
//!                              vector "v";
//!   Rotate3D(ang,p1,p2)      - rotation through the angle "ang"
//!                              counterclockwise around the axis given by
//!                              two points p1->p2;
//!   Rotate3D(a1,a2, b1,b2)   - rotation around the origin defined by initial
//!                              and transformed positions of two points;
//!   RotateX3D(ang)           - rotation around X-axis;
//!   RotateY3D(ang)           - rotation around Y-axis;
//!   RotateZ3D(ang)           - rotation around Z-axis;
//!
//! Inverse transformation:
//!   m.inverse() or           - returns inverse transformation;
//!
//! Compound transformation:
//!   m3 = m2 * m1             - it is relatively slow in comparison with
//!                              transformation of a vector. Use parenthesis
//!                              to avoid this operation (see example below);
//!
//! Several specialized classes are derived from it:
//!
//! RotateX3D,    RotateY3D,    RotateZ3D,    Rotate3D.
//!
//! The idea behind these classes is to provide some additional constructors
//! for Transform3D, they normally should not be used as separate classes.
//!
//! Example:
//! @code
//!   Transform3D m;
//!   m = TranslateX3D(10.*cm);
//! @endcode
//!
//! @author <Evgueni.Tcherniaev@cern.ch> 1996-2003
//!
class Transform3D {
  protected:
    // 4x3  Transformation Matrix
    double xx_, xy_, xz_,     
           yx_, yy_, yz_,
           zx_, zy_, zz_;

    //! Protected constructor.
    Transform3D(double XX, double XY, double XZ,
                double YX, double YY, double YZ,
                double ZX, double ZY, double ZZ)
        : xx_(XX), xy_(XY), xz_(XZ),
          yx_(YX), yy_(YY), yz_(YZ),
          zx_(ZX), zy_(ZY), zz_(ZZ) {}

    //! Sets transformation matrix.
    void setTransform(double XX, double XY, double XZ,
                      double YX, double YY, double YZ,
                      double ZX, double ZY, double ZZ) {
        xx_ = XX; xy_ = XY; xz_ = XZ;
        yx_ = YX; yy_ = YY; yz_ = YZ;
        zx_ = ZX; zy_ = ZY; zz_ = ZZ;
    }

  public:
    //! Global identity transformation. */
    static const Transform3D Identity;

    //! Helper class for implemention of C-style subscripting r[i][j] 
    class Transform3D_row {
      public:
        inline Transform3D_row(const Transform3D&, int);
        inline double operator [] (int) const;
      private:
        const Transform3D& rr;
        int ii;
    };

    //! Default constructor - sets the Identity transformation.
    Transform3D()
        : xx_(1), xy_(0), xz_(0),
          yx_(0), yy_(1), yz_(0),
          zx_(0), zy_(0), zz_(1) {}
  
    //! Copy constructor.
    Transform3D(const Transform3D& m)
        : xx_(m.xx_), xy_(m.xy_), xz_(m.xz_),
          yx_(m.yx_), yy_(m.yy_), yz_(m.yz_),
          zx_(m.zx_), zy_(m.zy_), zz_(m.zz_) {}

    //! Destructor. 
    //! Virtual for now as some persistency mechanism needs that,
    //! in future releases this might go away again.
    virtual ~Transform3D() {}

    //! Returns object of the helper class for C-style subscripting r[i][j]
    inline const Transform3D_row operator [] (int) const; 

    //! Fortran-style subscripting: returns (i,j) element of the matrix.
    double operator () (int, int) const;

    //! Gets xx-element of the transformation matrix.
    double xx() const { return xx_; }
    //! Gets xy-element of the transformation matrix.
    double xy() const { return xy_; }
    //! Gets xz-element of the transformation matrix.
    double xz() const { return xz_; }
    //! Gets yx-element of the transformation matrix.
    double yx() const { return yx_; }
    //! Gets yy-element of the transformation matrix.
    double yy() const { return yy_; }
    //! Gets yz-element of the transformation matrix.
    double yz() const { return yz_; }
    //! Gets zx-element of the transformation matrix.
    double zx() const { return zx_; }
    //! Gets zy-element of the transformation matrix.
    double zy() const { return zy_; }
    //! Gets zz-element of the transformation matrix.
    double zz() const { return zz_; }
    
    //! Assignment.
    Transform3D& operator=(const Transform3D&m) {
        xx_= m.xx_; xy_= m.xy_; xz_= m.xz_;
        yx_= m.yx_; yy_= m.yy_; yz_= m.yz_;
        zx_= m.zx_; zy_= m.zy_; zz_= m.zz_;
        return *this;
    }

    //! Sets the Identity transformation.
    void setIdentity() { 
        xy_= xz_= yx_= yz_= zx_= zy_= 0; xx_= yy_= zz_= 1;
    }
    
    //! Returns the inverse transformation.
    Transform3D inverse() const;
    
    //! Concatenation of transforms. Read efficiency warning!
    //!
    //! Warning:
    //! Do not use this function for one-time computations:
    //! Transform3D*Transform3D is roughly 3 times slower than
    //! Transform3D*Vector3D. Therefore prefer v2 = m3*(m2*(m1*v1))
    //! over v2 = m3*m2*m1*v1. (The latter expression is written
    //! without parentheses because operator* is left associative).
    //!
    //! Use of Transform3D*Transform3D is reasonable when the
    //! resulting transformation will be used several times.
    //!
    Transform3D operator*(const Transform3D& b) const;
    };

// ************************************************************************** //
//  Inlines that involve both Transform3D and Transform3D_row
// ************************************************************************** //

inline
Transform3D::Transform3D_row::Transform3D_row(const Transform3D & r, int i)
    : rr(r), ii(i) {}

inline
double Transform3D::Transform3D_row::operator[](int jj) const
    { return rr(ii,jj); }

inline
const Transform3D::Transform3D_row Transform3D::operator[](int i) const
    { return Transform3D_row(*this, i); }

}  // namespace Geometry

#endif /* GEOMETRY_TRANSFROM3D_H */

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
//! - reworked doxygen comments
//
// ************************************************************************** //

#ifndef GEOMETRY_TRANSFROM3D_H
#define GEOMETRY_TRANSFROM3D_H

#include <cmath>
#include "Point3D.h"
#include "Vector3D.h"
#include "Normal3D.h"

namespace Geometry {

class Translate3D;
class Rotate3D;
class Scale3D;

// ************************************************************************** //
//  Main class Transform3D
// ************************************************************************** //

//! Transformations of 3D geometrical objects (points, vectors, normals).

//! Uses a 4x3 double-precision transform matrix to rotate, translate,
//! reflect and scale.
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
//! Translations:
//!   Translate3D(v)           - translation given by CLHEP::Hep3Vector "v";
//!   Translate3D(dx,dy,dz)    - translation on vector (dx,dy,dz);
//!   TraslateX3D(dx)          - translation along X-axis;
//!   TraslateY3D(dy)          - translation along Y-axis;
//!   TraslateZ3D(dz)          - translation along Z-axis;
//!
//! Reflections:
//!   Reflect3D(a,b,c,d)       - reflection in the plane a*x+b*y+c*z+d=0;
//!   Reflect3D(normal,p)      - reflection in the plane going through "p"
//!                              and whose normal is equal to "normal";
//!   ReflectX3D(a)            - reflect X in the plane x=a (default a=0);
//!   ReflectY3D(a)            - reflect Y in the plane y=a (default a=0);
//!   ReflectZ3D(a)            - reflect Z in the plane z=a (default a=0);
//!
//! Scalings:
//!   Scale3D(sx,sy,sz)        - general scaling with factors "sx","sy","sz"
//!                                 along X, Y and Z;
//!   Scale3D(s)               - scaling with constant factor "s" along all 
//!                                 directions;
//!   ScaleX3D(sx)             - scale X;
//!   ScaleY3D(sy)             - scale Y;
//!   ScaleZ3D(sz)             - scale Z;
//!
//! Inverse transformation:
//!   m.inverse() or           - returns inverse transformation;
//!
//! Compound transformation:
//!   m3 = m2 * m1             - it is relatively slow in comparison with
//!                              transformation of a vector. Use parenthesis
//!                              to avoid this operation (see example below);
//! Transformation of point:
//!   p2 = m * p1
//!
//! Transformation of vector:
//!   v2 = m * v1
//!
//! Transformation of normal:
//!   n2 = m * n1
//!
//! The following table explains how different transformations affect
//! point, vector and normal. "+" means affect, "-" means do not affect,
//! "*" meas affect but in different way than "+" 
//!
//!                     Point  Vector  Normal
//!      -------------+-------+-------+-------
//!       Rotation    !   +   !   +   !   +
//!       Translation !   +   !   -   !   -
//!       Reflection  !   +   !   +   !   *
//!       Scaling     !   +   !   +   !   *
//!      -------------+-------+-------+-------
//!
//! Example of the usage:
//!
//!   Transform3D   m1, m2, m3;
//!   BasicVector3D v2, v1(0,0,0);
//!
//!   m1 = Rotate3D(angle, Vector3D(1,1,1));
//!   m2 = Translate3D(dx,dy,dz);
//!   m3 = m1.inverse();
//!
//!   v2 = m3*(m2*(m1*v1));
//!
//! Several specialized classes are derived from it:
//!
//! TranslateX3D, TranslateY3D, TranslateZ3D, Translate3D,<br>
//! RotateX3D,    RotateY3D,    RotateZ3D,    Rotate3D,   <br>
//! ScaleX3D,     ScaleY3D,     ScaleZ3D,     Scale3D,    <br>
//! ReflectX3D,   ReflectY3D,   ReflectZ3D,   Reflect3D.
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
    double xx_, xy_, xz_, dx_,     
           yx_, yy_, yz_, dy_,
           zx_, zy_, zz_, dz_;

    //! Protected constructor.
    Transform3D(double XX, double XY, double XZ, double DX,
                double YX, double YY, double YZ, double DY,
                double ZX, double ZY, double ZZ, double DZ)
        : xx_(XX), xy_(XY), xz_(XZ), dx_(DX),
          yx_(YX), yy_(YY), yz_(YZ), dy_(DY),
          zx_(ZX), zy_(ZY), zz_(ZZ), dz_(DZ) {}

    //! Sets transformation matrix.
    void setTransform(double XX, double XY, double XZ, double DX,
                      double YX, double YY, double YZ, double DY,
                      double ZX, double ZY, double ZZ, double DZ) {
        xx_ = XX; xy_ = XY; xz_ = XZ; dx_ = DX;
        yx_ = YX; yy_ = YY; yz_ = YZ; dy_ = DY;
        zx_ = ZX; zy_ = ZY; zz_ = ZZ; dz_ = DZ;
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
        : xx_(1), xy_(0), xz_(0), dx_(0),
          yx_(0), yy_(1), yz_(0), dy_(0),
          zx_(0), zy_(0), zz_(1), dz_(0) {}
  
    //! Constructor: transformation of basis (assumed - no reflection).
    Transform3D(const Point3D<double>& fr0,
                const Point3D<double>& fr1,
                const Point3D<double>& fr2,
                const Point3D<double>& to0,
                const Point3D<double>& to1,
                const Point3D<double>& to2);

    //! Copy constructor.
    Transform3D(const Transform3D& m)
        : xx_(m.xx_), xy_(m.xy_), xz_(m.xz_), dx_(m.dx_),
          yx_(m.yx_), yy_(m.yy_), yz_(m.yz_), dy_(m.dy_),
          zx_(m.zx_), zy_(m.zy_), zz_(m.zz_), dz_(m.dz_) {}

    //! Destructor. 
    //! Virtual for now as some persistency mechanism needs that,
    //! in future releases this might go away again.
    virtual ~Transform3D() { /* nop */ }

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
    //! Gets dx-element of the transformation matrix.
    double dx() const { return dx_; }
    //! Gets dy-element of the transformation matrix.
    double dy() const { return dy_; }
    //! Gets dz-element of the transformation matrix.
    double dz() const { return dz_; }
    
    //! Assignment.
    Transform3D& operator=(const Transform3D&m) {
        xx_= m.xx_; xy_= m.xy_; xz_= m.xz_; dx_= m.dx_;
        yx_= m.yx_; yy_= m.yy_; yz_= m.yz_; dy_= m.dy_;
        zx_= m.zx_; zy_= m.zy_; zz_= m.zz_; dz_= m.dz_;
        return *this;
    }

    //! Sets the Identity transformation.
    void setIdentity() { 
        xy_= xz_= dx_= yx_= yz_= dy_= zx_= zy_= dz_= 0; xx_= yy_= zz_= 1;
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
    
    //! Decomposition of general transformation.
    //!
    //! This function returns a decomposition of the transformation
    //! into three sequential transformations: Scale3D,
    //! then Rotate3D, then Translate3, i.e.
    //! @code
    //!   Transform3D = Translate3D * Rotate3D * Scale3D
    //! @endcode
    //!
    //! @param scale       output: scaling transformation;
    //!                    if there was a reflection, then scale factor for
    //!                    z-component (scale(2,2)) will be negative.
    //! @param rotation    output: rotation transformaion.
    //! @param translation output: translation transformaion.
    void getDecomposition(Scale3D& scale,
                          Rotate3D& rotation,
                          Translate3D& translation) const;

    //! Test for equality.
    bool operator == (const Transform3D& transform) const;
    
    //! Test for inequality.
    bool operator != (const Transform3D& transform) const {
        return ! operator==(transform);
    }

    //! Difference between corresponding matrix elements less than tolerance?
    bool isNear(const Transform3D& t, double tolerance = 2.2E-14 ) const;
};

// ************************************************************************** //
//   Rotations
// ************************************************************************** //

//! A rotation of 3D geometrical objects (points, vectors, normals).

//! This class provides additional constructors for Transform3D
//! and should not be used as a separate class.
//! 
//! Example of use:
//! @code
//!   Transform3D m;
//!   m = Rotate3D(30.*deg, HepVector3D(1.,1.,1.));
//! @endcode
//!
//! @author <Evgueni.Tcherniaev@cern.ch> 1996-2003
//!
class Rotate3D : public Transform3D {
public:
    //! Default constructor: sets the Identity transformation.
    Rotate3D() : Transform3D() {}
    
    //! Construct rotation by angle a around axis p1->p2.
    Rotate3D(double a,
	     const Point3D<double>& p1,
	     const Point3D<double>& p2);
    
    //! Constructor from original and rotated position of two points.

    //! It is assumed that there is no reflection.
    //! @param fr1 original position of 1st point
    //! @param fr2 original position of 2nd point
    //! @param to1 rotated position of 1st point
    //! @param to2 rotated position of 2nd point
    inline Rotate3D(const Point3D<double>& fr1,
		    const Point3D<double>& fr2,
		    const Point3D<double>& to1,
		    const Point3D<double>& to2)
        : Transform3D(Point3D<double>(0.0, 0.0, 0.0),fr1,fr2,
                      Point3D<double>(0.0, 0.0, 0.0),to1,to2) {}


    //! Constructor from angle and axis.

    //! @param a angle of rotation
    //! @param v axis of rotation
    inline Rotate3D(double a, const Vector3D<double>& v)
    //  TODO(C++11): simplify using delegating constructor
    { *this = Rotate3D(a, Point3D<double>(0.0, 0.0, 0.0),
                       Point3D<double>(v.x(),v.y(),v.z()) ); }
};

//! A rotation of 3D geometrical objects around the x-axis.

//! Should not be instantiated: see Rotate3D for example of use.
//!
//! @author <Evgueni.Tcherniaev@cern.ch>
//!
class RotateX3D : public Rotate3D {
public:
    //! Default constructor: sets the Identity transformation.
    RotateX3D() : Rotate3D() {}
    
    //! Constructs a rotation around x-axis by angle a.
    RotateX3D(double a) {
        double cosa = std::cos(a), sina = std::sin(a); 
        setTransform(1.0,0.0,0.0,0.0,  0.0,cosa,-sina,0.0,  0.0,sina,cosa,0.0);
    }
};

//! A rotation of 3D geometrical objects around the y-axis.

//! Should not be instantiated: see Rotate3D for example of use.
//!
//! @author <Evgueni.Tcherniaev@cern.ch>
//!
class RotateY3D : public Rotate3D {
public:
    //! Default constructor: sets the Identity transformation.
    RotateY3D() : Rotate3D() {}
    
    //! Constructs a rotation around y-axis by angle a.
    RotateY3D(double a) {
        double cosa = std::cos(a), sina = std::sin(a); 
        setTransform(cosa,0.0,sina,0.0,  0.0,1.0,0.0,0.0,  -sina,0.0,cosa,0.0);
    }
};

//! A rotation of 3D geometrical objects around the z-axis.

//! Should not be instantiated: see Rotate3D for example of use.
//!
//! @author <Evgueni.Tcherniaev@cern.ch>
//!
class RotateZ3D : public Rotate3D {
public:
    //! Default constructor: sets the Identity transformation.
    RotateZ3D() : Rotate3D() {}
    
    //! Constructs a rotation around z-axis by angle a.
    RotateZ3D(double a) {
        double cosa = std::cos(a), sina = std::sin(a); 
        setTransform(cosa,-sina,0.0,0.0,  sina,cosa,0.0,0.0,  0.0,0.0,1.0,0.0);
    }
};

// ************************************************************************** //
//  Translations
// ************************************************************************** //
  
//! A translation of 3D geometrical objects (points, vectors, normals).

//! This class provides additional constructors for Transform3D
//! and should not be used as a separate class.
//! 
//! Example of use:
//! @code
//!   Transform3D m;
//!   m = Translate3D(10.,20.,30.);
//! @endcode
//!
//! @author <Evgueni.Tcherniaev@cern.ch> 1996-2003
//!
class Translate3D : public Transform3D {
public:
    //! Default constructor: sets the Identity transformation.
    Translate3D() : Transform3D() {}

    //! Constructor from three numbers.
    Translate3D(double x, double y, double z)
        : Transform3D(1.0,0.0,0.0,x, 0.0,1.0,0.0,y, 0.0,0.0,1.0,z) {}
};

//! A translation along the x-axis.

//! Should not be instantiated: see Translate3D for example of use.
//!
class TranslateX3D : public Translate3D {
public:
    //! Default constructor: sets the Identity transformation.
    TranslateX3D() : Translate3D() {}
    
    //! Constructor from a number.
    TranslateX3D(double x) : Translate3D(x, 0.0, 0.0) {}
};

//! A translation along the y-axis.

//! Should not be instantiated: see Translate3D for example of use.
//!
class TranslateY3D : public Translate3D {
public:
    //! Default constructor: sets the Identity transformation.
    TranslateY3D() : Translate3D() {}

    //! Constructor from a number.
    TranslateY3D(double y) : Translate3D(0.0, y, 0.0) {}
};

//! A translation along the z-axis.

//! Should not be instantiated: see Translate3D for example of use.
//!
class TranslateZ3D : public Translate3D {
public:
    //! Default constructor: sets the Identity transformation.
    TranslateZ3D() : Translate3D() {}

    //! Constructor from a number.
    TranslateZ3D(double z) : Translate3D(0.0, 0.0, z) {}
};

// ************************************************************************** //
//  Reflections
// ************************************************************************** //

//! A reflection transformation.

//! This class provides additional constructors for Transform3D
//! and should not be used as a separate class.
//! 
//! Example of use:
//! @code
//!   Transform3D m;
//!   m = Reflect3D(1.,1.,1.,0.);
//! @endcode
//!
//! @author <Evgueni.Tcherniaev@cern.ch>

class Reflect3D : public Transform3D {
protected:
    Reflect3D(double XX, double XY, double XZ, double DX,
              double YX, double YY, double YZ, double DY,
              double ZX, double ZY, double ZZ, double DZ)
        : Transform3D(XX,XY,XZ,DX, YX,YY,YZ,DY, ZX,ZY,ZZ,DZ) {}

public:
    //! Default constructor: sets the Identity transformation.
    Reflect3D() : Transform3D() {}

    //! Construct reflection from a plane a*x+b*y+c*z+d=0.
    Reflect3D(double a, double b, double c, double d);

    //! Construct reflection from a plane given by its normal a point.

    inline Reflect3D(const Normal3D<double>& normal,
                     const Point3D<double>& point) 
    //  TODO(C++11): simplify using delegating constructor
    { *this = Reflect3D(normal.x(), normal.y(), normal.z(), -normal*point); }
};

//! A reflection in a plane x=const.

//! Should not be instantiated: see Reflect3D for example of use.
//!
class ReflectX3D : public Reflect3D {
public:
    //! Constructor from a number.
    ReflectX3D(double x=0)
        : Reflect3D(-1.0,0.0,0.0,x+x, 0.0,1.0,0.0,0.0, 0.0,0.0,1.0,0.0) {}
};
 
//! A reflection in a plane y=const.

//! Should not be instantiated: see Reflect3D for example of use.
//!
class ReflectY3D : public Reflect3D {
public:
    //! Constructor from a number.
    ReflectY3D(double y=0)
        : Reflect3D(1.0,0.0,0.0,0.0, 0.0,-1.0,0.0,y+y, 0.0,0.0,1.0,0.0) {}
};
 
//! A reflection in a plane z=const.

//! Should not be instantiated: see Reflect3D for example of use.
//!
class ReflectZ3D : public Reflect3D {
public:
    //! Constructor from a number.
    ReflectZ3D(double z=0)
        : Reflect3D(1.0,0.0,0.0,0.0, 0.0,1.0,0.0,0.0, 0.0,0.0,-1.0,z+z) {}
};
 
// ************************************************************************** //
//  Scalings
// ************************************************************************** //

//! A scaling transformation.

//! This class provides additional constructors for Transform3D
//! and should not be used as a separate class.
//! 
//! Example of use:
//! @code
//!   Transform3D m;
//!   m = Scale3D(2.);
//! @endcode
//!
//! @author <Evgueni.Tcherniaev@cern.ch>
//!
class Scale3D : public Transform3D {
public:
    //! Default constructor: sets the Identity transformation.
    Scale3D() : Transform3D() {}

    //! Constructor from three numbers - scale factors in different directions.
    Scale3D(double x, double y, double z)
        : Transform3D(x,0.0,0.0,0.0, 0.0,y,0.0,0.0, 0.0,0.0,z,0.0) {}

    //! Constructor from a number: sets uniform scaling in all directions.
    Scale3D(double s)
    : Transform3D(s,0.0,0.0,0.0, 0.0,s,0.0,0.0, 0.0,0.0,s,0.0) {}
};

//! A scaling transformation in x-direction.

//! Should not be instantiated: see Scale3D for example of use.
//!
class ScaleX3D : public Scale3D {
public:
    //! Default constructor: sets the Identity transformation.
    ScaleX3D() : Scale3D() {}

    //! Constructor from a number (scale factor in x-direction).
    ScaleX3D(double x) : Scale3D(x, 1.0, 1.0) {}
};

//! A scaling transformation in y-direction.

//! Should not be instantiated: see Scale3D for example of use.
//!
class ScaleY3D : public Scale3D {
public:
    //! Default constructor: sets the Identity transformation.
    ScaleY3D() : Scale3D() {}

    //! Constructor from a number (scale factor in y-direction).
    ScaleY3D(double y) : Scale3D(1.0, y, 1.0) {}
};

//! A scaling transformation in z-direction.

//! Should not be instantiated: see Scale3D for example of use.
//!
class ScaleZ3D : public Scale3D {
public:
    //! Default constructor: sets the Identity transformation.
    ScaleZ3D() : Scale3D() {}

    //! Constructor from a number (scale factor in z-direction).
    ScaleZ3D(double z) : Scale3D(1.0, 1.0, z) {}
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

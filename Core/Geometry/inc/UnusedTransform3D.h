// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file       Geometry/src/Transform3D.cpp
//! @brief      Implements class Transform3D.
//!
//! For historic note, see BasicVector3D.h.
//!
//! @homepage   http://apps.jcns.fz-juelich.de/BornAgain
//! @license    GNU General Public License v3 or higher (see COPYING)
//! @copyright  Forschungszentrum Jülich GmbH 2013
//! @authors    C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include <iostream>
#include <cmath>	// double std::abs()
#include <stdlib.h>	// int std::abs()
#include "Transform3D.h"
#include "Exceptions.h"

namespace Geometry {

//! @brief Constructs a rotation by angle _a_
//!        around an axis pointing from _p1_ to _p2_.

//! @author E. Chernyaev 1996 (CLHEP/Geometry)
//!
Transform3D::Transform3D(double a,
                         const BasicVector3D<double>& p1,
                         const BasicVector3D<double>& p2)
{
    if (a == 0)
        return Transform3D();  // identity transform

    double cx = p2.x()-p1.x(), cy = p2.y()-p1.y(), cz = p2.z()-p1.z();
    double ll = std::sqrt(cx*cx + cy*cy + cz*cz);
    if (ll == 0)
        throw RuntimeErrorException(
            "Transform3D::Transform3D(a,p1,p2) -> "
            "Error: no rotation axis given (zero length)");
    double cosa = std::cos(a);
    double sina = std::sin(a);
    cx /= ll; cy /= ll; cz /= ll;
    
    xx_ = (1-cosa)*cx*cx + cosa;
    xy_ = (1-cosa)*cx*cy - sina*cz;
    xz_ = (1-cosa)*cx*cz + sina*cy;

    yx_ = (1-cosa)*cy*cx + sina*cz;
    yy_ = (1-cosa)*cy*cy + cosa;
    yz_ = (1-cosa)*cy*cz - sina*cx;

    zx_ = (1-cosa)*cz*cx - sina*cy;
    zy_ = (1-cosa)*cz*cy + sina*cx;
    zz_ = (1-cosa)*cz*cz + cosa;
}

//! Returns the inverse transformation.

//! @author E. Chernyaev 1996 (CLHEP/Geometry)
//!
Transform3D Transform3D::inverse() const
{
    double detxx = yy_*zz_-yz_*zy_;
    double detxy = yx_*zz_-yz_*zx_;
    double detxz = yx_*zy_-yy_*zx_;
    double det   = xx_*detxx - xy_*detxy + xz_*detxz;
    if (det == 0)
        throw RuntimeErrorException( "Transform3D::inverse() -> "
                                     "Error: zero determinant" );
    det = 1./det; detxx *= det; detxy *= det; detxz *= det;
    double detyx = (xy_*zz_ - xz_*zy_)*det;
    double detyy = (xx_*zz_ - xz_*zx_)*det;
    double detyz = (xx_*zy_ - xy_*zx_)*det;
    double detzx = (xy_*yz_ - xz_*yy_)*det;
    double detzy = (xx_*yz_ - xz_*yx_)*det;
    double detzz = (xx_*yy_ - xy_*yx_)*det;
    return *this = Transform3D( detxx, -detyx,  detzx,
                                -detxy,  detyy, -detzy,
                                detxz, -detyz,  detzz );
}

}  // namespace Geometry




    //! @brief Constructs a rotation by angle _a_
    //!        around an axis pointing from _p1_ to _p2_.
    Transform3D(double a,
                const BasicVector3D<double>& p1,
                const BasicVector3D<double>& p2);

    //! Constructs a rotation by angle _a_ around axis _v_.
    Transform3D(double a, const BasicVector3D<double>& v)
    //  TODO(C++11): simplify using delegating constructor
    {
        *this = Transform3D(a,
                            BasicVector3D<double>(0., 0., 0.),
                            BasicVector3D<double>(v.x(),v.y(),v.z()) );
    }

    //! Copy constructor.
    Transform3D(const Transform3D& m)
        : xx_(m.xx_), xy_(m.xy_), xz_(m.xz_),
          yx_(m.yx_), yy_(m.yy_), yz_(m.yz_),
          zx_(m.zx_), zy_(m.zy_), zz_(m.zz_) {}

    //! Destructor.
    virtual ~Transform3D() {}

    //! Assignment.
    Transform3D& operator=(const Transform3D&m) {
        xx_= m.xx_; xy_= m.xy_; xz_= m.xz_;
        yx_= m.yx_; yy_= m.yy_; yz_= m.yz_;
        zx_= m.zx_; zy_= m.zy_; zz_= m.zz_;
        return *this;
    }

    //! Returns xx-element of the transformation matrix.
    double xx() const { return xx_; }
    //! Returns xy-element of the transformation matrix.
    double xy() const { return xy_; }
    //! Returns xz-element of the transformation matrix.
    double xz() const { return xz_; }
    //! Returns yx-element of the transformation matrix.
    double yx() const { return yx_; }
    //! Returns yy-element of the transformation matrix.
    double yy() const { return yy_; }
    //! Returns yz-element of the transformation matrix.
    double yz() const { return yz_; }
    //! Returns zx-element of the transformation matrix.
    double zx() const { return zx_; }
    //! Returns zy-element of the transformation matrix.
    double zy() const { return zy_; }
    //! Returns zz-element of the transformation matrix.
    double zz() const { return zz_; }
    
    //! Sets the Identity transformation.
    void setIdentity() { 
        xy_= xz_= yx_= yz_= zx_= zy_= 0; xx_= yy_= zz_= 1;
    }
    
    //! Returns the inverse transformation.
    Transform3D inverse() const;
    
    //! Return transformed (typically: rotated) vector _v_.
    virtual BasicVector3D<double> transformed(const BasicVector3D<double>& v) const
    {
        return BasicVector3D<double>(
            xx()*v.x() + xy()*v.y() + xz()*v.z(),
            yx()*v.x() + yy()*v.y() + yz()*v.z(),
            zx()*v.x() + zy()*v.y() + zz()*v.z());
    }

 protected:
    // 3x3  Transformation Matrix
    double xx_, xy_, xz_,     
           yx_, yy_, yz_,
           zx_, zy_, zz_;

    //! Constructor to set all 9 matrix elements, for internal use only.
    Transform3D(double XX, double XY, double XZ,
                double YX, double YY, double YZ,
                double ZX, double ZY, double ZZ)
        : xx_(XX), xy_(XY), xz_(XZ),
          yx_(YX), yy_(YY), yz_(YZ),
          zx_(ZX), zy_(ZY), zz_(ZZ) {}
};

//! A rotation of 3D geometrical objects around the x-axis.

//! Should not be instantiated: see Rotate3D for example of use.
//!
//! @author <Evgueni.Tcherniaev@cern.ch>
//!
class RotateX3D : public Transform3D {
 public:
    //! Default constructor: sets the identity transformation.
    RotateX3D() : Transform3D() {}
    
    //! Constructs a rotation around x-axis by angle a.
    RotateX3D(double a) {
        double cosa = std::cos(a), sina = std::sin(a); 
        setTransform(1.,0.,0., 0.,cosa,-sina, 0.,sina,cosa);
    }
};

//! A rotation of 3D geometrical objects around the y-axis.

//! Should not be instantiated: see Transform3D for example of use.
//!
//! @author <Evgueni.Tcherniaev@cern.ch>
//!
class RotateY3D : public Transform3D {
 public:
    //! Default constructor: sets the identity transformation.
    RotateY3D() : Transform3D() {}
    
    //! Constructs a rotation around y-axis by angle a.
    RotateY3D(double a) {
        double cosa = std::cos(a), sina = std::sin(a); 
        setTransform(cosa,0.,sina, 0.,1.,0., -sina,0.,cosa);
    }
};

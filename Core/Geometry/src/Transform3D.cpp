// ************************************************************************** //
//
//  heinzlibs:  Library collection of the Scientific Computing Group at
//              Heinz Maier-Leibnitz Zentrum (MLZ) Garching
//
//  libgeo3d:   Library for three-dimensional Euclidian geometry,
//              based on CLHEP/Geometry 1.9 of 1.4.2003,
//              forked after v 1.6 2003/10/24 21:39:45
//
//! @file       Geometry/src/Transform3D.cpp
//! @brief      implements core methods of class Transform3D.
//!
//! @homepage   http://apps.jcns.fz-juelich.de/BornAgain
//! @license    GNU General Public License v3 or higher (see COPYING)
//! @copyright  Forschungszentrum Jülich GmbH 2013
//! @authors    E. Chernyaev <Evgueni.Tcherniaev@cern.ch> 1996-2003
//! @authors    C. Durniak, G. Pospelov, W. Van Herck, J. Wuttke
//!
//! Changes w.r.t. CLHEP:
//! - eliminated support for type float
//! - reworked doxygen comments
//
// ************************************************************************** //

#include <iostream>
#include <cmath>	// double std::abs()
#include <stdlib.h>	// int std::abs()
#include "Transform3D.h"

namespace Geometry {

const Transform3D Transform3D::Identity = Transform3D ();

double Transform3D::operator () (int i, int j) const
{
    if (i == 0) {
        if (j == 0) { return xx_; }
        if (j == 1) { return xy_; }
        if (j == 2) { return xz_; }
        if (j == 3) { return dx_; }
    } else if (i == 1) {
        if (j == 0) { return yx_; }
        if (j == 1) { return yy_; }
        if (j == 2) { return yz_; }
        if (j == 3) { return dy_; }
    } else if (i == 2) {
        if (j == 0) { return zx_; }
        if (j == 1) { return zy_; }
        if (j == 2) { return zz_; }
        if (j == 3) { return dz_; }
    } else if (i == 3) {
        if (j == 0) { return 0.0; }
        if (j == 1) { return 0.0; }
        if (j == 2) { return 0.0; }
        if (j == 3) { return 1.0; }
    }
    std::cerr << "Transform3D subscripting: bad indeces "
              << "(" << i << "," << j << ")" << std::endl;
    return 0.0;
}

//! Concatenation of transforms. Read efficiency warning!

Transform3D Transform3D::operator*(const Transform3D & b) const
{
    return Transform3D
            (xx_*b.xx_+xy_*b.yx_+xz_*b.zx_, xx_*b.xy_+xy_*b.yy_+xz_*b.zy_,
             xx_*b.xz_+xy_*b.yz_+xz_*b.zz_, xx_*b.dx_+xy_*b.dy_+xz_*b.dz_+dx_,
             yx_*b.xx_+yy_*b.yx_+yz_*b.zx_, yx_*b.xy_+yy_*b.yy_+yz_*b.zy_,
             yx_*b.xz_+yy_*b.yz_+yz_*b.zz_, yx_*b.dx_+yy_*b.dy_+yz_*b.dz_+dy_,
             zx_*b.xx_+zy_*b.yx_+zz_*b.zx_, zx_*b.xy_+zy_*b.yy_+zz_*b.zy_,
             zx_*b.xz_+zy_*b.yz_+zz_*b.zz_, zx_*b.dx_+zy_*b.dy_+zz_*b.dz_+dz_);
}

//! Constructor: transformation of basis (assumed - no reflection).

//! Transformation from coordinate system defined by its origin "fr0"
//! and two axes "fr0->fr1", "fr0->fr2" to another coordinate system
//! "to0", "to0->to1", "to0->to2"
//!
//! @author E. Chernyaev 1996-2003

Transform3D::Transform3D(const Point3D<double> & fr0,
                         const Point3D<double> & fr1,
                         const Point3D<double> & fr2,
                         const Point3D<double> & to0,
                         const Point3D<double> & to1,
                         const Point3D<double> & to2)
    : xx_(1), xy_(0), xz_(0), dx_(0),
      yx_(0), yy_(1), yz_(0), dy_(0),
      zx_(0), zy_(0), zz_(1), dz_(0)
{
    Vector3D<double> x1,y1,z1, x2,y2,z2;
    x1 = (fr1 - fr0).unit();
    y1 = (fr2 - fr0).unit();
    x2 = (to1 - to0).unit();
    y2 = (to2 - to0).unit();
    
    // -- Check angles --
    
    double cos1, cos2;
    cos1 = x1.dot(y1);
    cos2 = x2.dot(y2);
    
    if (std::abs(1.0-cos1) <= 0.000001 || std::abs(1.0-cos2) <= 0.000001) {
        std::cerr << "Transform3D: zero angle between axes" << std::endl;
        setIdentity();
    } else {
        if (std::abs(cos1-cos2) > 0.000001) {
            std::cerr << "Transform3D: angles between axes are not equal"
                      << std::endl;
        }

        // -- Find rotation matrix --

        z1 = (x1.cross(y1)).unit();
        y1  = z1.cross(x1);

        z2 = (x2.cross(y2)).unit();
        y2  = z2.cross(x2);

        double detxx =  (y1.y()*z1.z() - z1.y()*y1.z());
        double detxy = -(y1.x()*z1.z() - z1.x()*y1.z());
        double detxz =  (y1.x()*z1.y() - z1.x()*y1.y());
        double detyx = -(x1.y()*z1.z() - z1.y()*x1.z());
        double detyy =  (x1.x()*z1.z() - z1.x()*x1.z());
        double detyz = -(x1.x()*z1.y() - z1.x()*x1.y());
        double detzx =  (x1.y()*y1.z() - y1.y()*x1.z());
        double detzy = -(x1.x()*y1.z() - y1.x()*x1.z());
        double detzz =  (x1.x()*y1.y() - y1.x()*x1.y());

        double txx = x2.x()*detxx + y2.x()*detyx + z2.x()*detzx;
        double txy = x2.x()*detxy + y2.x()*detyy + z2.x()*detzy;
        double txz = x2.x()*detxz + y2.x()*detyz + z2.x()*detzz;
        double tyx = x2.y()*detxx + y2.y()*detyx + z2.y()*detzx;
        double tyy = x2.y()*detxy + y2.y()*detyy + z2.y()*detzy;
        double tyz = x2.y()*detxz + y2.y()*detyz + z2.y()*detzz;
        double tzx = x2.z()*detxx + y2.z()*detyx + z2.z()*detzx;
        double tzy = x2.z()*detxy + y2.z()*detyy + z2.z()*detzy;
        double tzz = x2.z()*detxz + y2.z()*detyz + z2.z()*detzz;

        // -- set transformation --

        double dx1 = fr0.x(), dy1 = fr0.y(), dz1 = fr0.z();
        double dx2 = to0.x(), dy2 = to0.y(), dz2 = to0.z();

        setTransform(txx, txy, txz, dx2-txx*dx1-txy*dy1-txz*dz1,
                     tyx, tyy, tyz, dy2-tyx*dx1-tyy*dy1-tyz*dz1,
                     tzx, tzy, tzz, dz2-tzx*dx1-tzy*dy1-tzz*dz1);
    }
}

//! Returns the inverse transformation.
//!
//! @author E. Chernyaev 1996

Transform3D Transform3D::inverse() const
{
    double detxx = yy_*zz_-yz_*zy_;
    double detxy = yx_*zz_-yz_*zx_;
    double detxz = yx_*zy_-yy_*zx_;
    double det   = xx_*detxx - xy_*detxy + xz_*detxz;
    if (det == 0) {
        std::cerr << "Transform3D::inverse error: zero determinant" << std::endl;
        return Transform3D();
    }
    det = 1./det; detxx *= det; detxy *= det; detxz *= det;
    double detyx = (xy_*zz_ - xz_*zy_)*det;
    double detyy = (xx_*zz_ - xz_*zx_)*det;
    double detyz = (xx_*zy_ - xy_*zx_)*det;
    double detzx = (xy_*yz_ - xz_*yy_)*det;
    double detzy = (xx_*yz_ - xz_*yx_)*det;
    double detzz = (xx_*yy_ - xy_*yx_)*det;
    return Transform3D
            (detxx, -detyx,  detzx, -detxx*dx_+detyx*dy_-detzx*dz_,
             -detxy,  detyy, -detzy,  detxy*dx_-detyy*dy_+detzy*dz_,
             detxz, -detyz,  detzz, -detxz*dx_+detyz*dy_-detzz*dz_);
}

}  // namespace Geometry

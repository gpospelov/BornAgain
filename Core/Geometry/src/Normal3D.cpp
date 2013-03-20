// ************************************************************************** //
//
//  heinzlibs:  Library collection of the Scientific Computing Group at
//              Heinz Maier-Leibnitz Zentrum (MLZ) Garching
//
//  libgeo3d:   Library for three-dimensional Euclidian geometry,
//              based on CLHEP/Geometry 1.9 of 1.4.2003,
//              forked after v 1.3 2003/08/13 20:00:11
//
//! @file       Geometry/src/Normal3D.cpp
//! @brief      implements some methods of class Normal3D<double>
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

#include "Normal3D.h"
#include "Transform3D.h"

namespace Geometry {

Normal3D<double>& Normal3D<double>::transform (const Transform3D & m)
{
    double vx = x(),    vy = y(),    vz = z();
    double xx = m.xx(), xy = m.xy(), xz = m.xz();
    double yx = m.yx(), yy = m.yy(), yz = m.yz();
    double zx = m.zx(), zy = m.zy(), zz = m.zz();
    setXYZ((yy*zz-yz*zy)*vx+(yz*zx-yx*zz)*vy+(yx*zy-yy*zx)*vz,
           (zy*xz-zz*xy)*vx+(zz*xx-zx*xz)*vy+(zx*xy-zy*xx)*vz,
           (xy*yz-xz*yy)*vx+(xz*yx-xx*yz)*vy+(xx*yy-xy*yx)*vz);
    return *this;
}

Normal3D<double> operator*(const Transform3D& m, const Normal3D<double>& v)
{
    double vx = v.x(),  vy = v.y(),  vz = v.z();
    double xx = m.xx(), xy = m.xy(), xz = m.xz();
    double yx = m.yx(), yy = m.yy(), yz = m.yz();
    double zx = m.zx(), zy = m.zy(), zz = m.zz();
    return Normal3D<double>
            ((yy*zz-yz*zy)*vx+(yz*zx-yx*zz)*vy+(yx*zy-yy*zx)*vz,
             (zy*xz-zz*xy)*vx+(zz*xx-zx*xz)*vy+(zx*xy-zy*xx)*vz,
             (xy*yz-xz*yy)*vx+(xz*yx-xx*yz)*vy+(xx*yy-xy*yx)*vz);
}

}  // namespace Geometry

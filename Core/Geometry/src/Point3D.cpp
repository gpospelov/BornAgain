// ************************************************************************** //
//
//  heinzlibs:  Library collection of the Scientific Computing Group at
//              Heinz Maier-Leibnitz Zentrum (MLZ) Garching
//
//  libgeo3d:   Library for three-dimensional Euclidian geometry,
//              based on CLHEP/Geometry 1.9 of 1.4.2003,
//              forked after v 1.3 2003/08/13 20:00:11
//
//! @file       Geometry/src/Point3D.cpp
//! @brief      implements some methods of class Point3D<double>
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

#include "Point3D.h"
#include "Transform3D.h"

namespace Geometry {

Point3D<double>& Point3D<double>::transform(
            const Transform3D& m)
{
    double vx = x(), vy = y(), vz = z();
    setXYZ(m.xx()*vx + m.xy()*vy + m.xz()*vz + m.dx(),
           m.yx()*vx + m.yy()*vy + m.yz()*vz + m.dy(),
           m.zx()*vx + m.zy()*vy + m.zz()*vz + m.dz());
    return *this;
}

Point3D<double> operator* (
            const Transform3D& m, const Point3D<double>& v)
{
    double vx = v.x(), vy = v.y(), vz = v.z();
    return Point3D<double>
            (m.xx()*vx + m.xy()*vy + m.xz()*vz + m.dx(),
             m.yx()*vx + m.yy()*vy + m.yz()*vz + m.dy(),
             m.zx()*vx + m.zy()*vy + m.zz()*vz + m.dz());
}

}  // namespace Geometry

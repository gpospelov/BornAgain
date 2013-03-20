// ************************************************************************** //
//
//  heinzlibs:  Library collection of the Scientific Computing Group at
//              Heinz Maier-Leibnitz Zentrum (MLZ) Garching
//
//  libgeo3d:   Library for three-dimensional Euclidian geometry,
//              based on CLHEP/Geometry 1.9 of 1.4.2003,
//              forked after v 1.4 2003/08/13 20:00:11
//
//! @file       Geometry/src/Plane3D.cpp
//! @brief      implements some methods of class Plane3D<double>
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
#include "Plane3D.h"

namespace Geometry {

std::ostream& operator<< (
        std::ostream& os, const Plane3D<double>& p)
{
    return os <<
        '(' << p.a() << ',' << p.b() << ',' << p.c() << ',' << p.d() << ')';
  }

}  // namespace Geometry

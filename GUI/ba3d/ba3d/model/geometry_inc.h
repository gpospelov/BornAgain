// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/model/geometry_inc.h
//! @brief     Defines geometry namespace
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BA3D_GEOMETRY_INC_H
#define BA3D_GEOMETRY_INC_H

#include "../def.h"
#include <QSharedPointer>

// include to use geometry basics, without details

namespace RealSpace {
//------------------------------------------------------------------------------

class Geometry;

typedef QSharedPointer<Geometry> shGeo;
typedef QWeakPointer<Geometry>   wkGeo;

namespace geometry {

// geometry enumerated id
enum class eid { Plane, Box, Sphere, Column,
                 Icosahedron, Dodecahedron, TruncatedBox,
                 Cuboctahedron };

// these come useful
extern float const GoldenRatio;
extern float const IcosahedronL2R;  // L/R conversion
extern float const DodecahedronL2R;

// geometries may have 1 or 2 float parameters; together with eid -> hash key
struct key {
  key(eid);
  key(eid, float);
  key(eid, float, float);

  eid id;
  float p1, p2;

  bool operator==(key const&) const;
};

uint qHash(key const&);

}

//------------------------------------------------------------------------------
}
#endif

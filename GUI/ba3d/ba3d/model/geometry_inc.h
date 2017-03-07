// GPL3; https://github.com/jburle/ba3d

#ifndef BA3D_GEOMETRY_INC_H
#define BA3D_GEOMETRY_INC_H

#include "../def.h"
#include <QSharedPointer>

// include to use geometry basics, without details

namespace ba3d {
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
extern flt const goldenRatio;
extern flt const icosahedronL2R;  // L/R conversion
extern flt const dodecahedronL2R;

// geometries may have 1 or 2 flt parameters; together with eid -> hash key
struct key {
  key(eid);
  key(eid, flt);
  key(eid, flt, flt);

  eid id;
  flt p1, p2;

  bool operator==(key const&) const;
};

uint qHash(key const&);

}

//------------------------------------------------------------------------------
}
#endif
// eof

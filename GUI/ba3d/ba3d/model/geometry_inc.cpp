// GPL3; https://github.com/jburle/ba3d

#include "geometry_inc.h"
#include <qmath.h>

namespace ba3d {
//------------------------------------------------------------------------------

flt const geometry::goldenRatio     = flt(1 + qSqrt(5)) / 2;
flt const geometry::icosahedronL2R  = flt(4 / (10 + 2*qSqrt(5)));
flt const geometry::dodecahedronL2R = flt(4 / qSqrt(3) / (1+qSqrt(5)));

//------------------------------------------------------------------------------

geometry::key::key(geometry::eid id) : key(id, 0, 0) {}

geometry::key::key(geometry::eid id, flt p1) : key(id, p1, 0) {}

geometry::key::key(eid id_, flt p1_, flt p2_)
  : id(id_), p1(p1_), p2(p2_) {
}

bool geometry::key::operator==(key const& that) const {
  return id == that.id && p1 == that.p1 && p2 == that.p2;
}

uint geometry::qHash(geometry::key const& key) {
  // the hash is simply a bitwise superposition of id, p1, p2
  union {
    flt           f;
    quint32       u;
    geometry::eid i;
  } id, p1, p2;

  id.i = key.id; p1.f = key.p1; p2.f = key.p2;
  return id.u | p1.u | p2.u;
}

//------------------------------------------------------------------------------
}
// eof

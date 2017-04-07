// GPL3; https://github.com/jburle/ba3d

#include "../geometry.h"
#include <qmath.h>
#include <QQuaternion>

namespace ba3d {
//------------------------------------------------------------------------------

Geometry::mesh_t Geometry::meshIcosahedron() {
  flt const G = geometry::goldenRatio;

  auto q = QQuaternion::rotationTo(-xyz::_z, xyz(0,1,-G));

  xyz_vec vs_; vs_.reserve(12);
  for (flt _1 : {-1, +1})
    for (flt g : {-G, +G}) {
      vs_.append(q.rotatedVector(xyz(0, _1, g)));
      vs_.append(q.rotatedVector(xyz(_1, g, 0)));
      vs_.append(q.rotatedVector(xyz(g, 0, _1)));
    }

  ENSURE(12 == vs_.count())

  // scale to circumscribed sphere
  flt const F = .5f / vs_.at(0).length();
  for (auto& v : vs_)
    v = v*F;

  xyz_vec vs; vs.reserve(60);

  vs.addFan(vs_, {0, 1, 2, 6, 5, 7, 1});
  vs.addFan(vs_, {9, 3, 11, 10, 4, 8, 3});
  vs.addStrip(vs_, {1, 3, 7, 11, 5, 10, 6, 4, 2, 8, 1, 3});

  ENSURE(60 == vs.count())

  return makeMesh(vs);
}

//------------------------------------------------------------------------------
}
// eof

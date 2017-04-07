// GPL3; https://github.com/jburle/ba3d

#include "../geometry.h"
#include <qmath.h>
#include <QQuaternion>

namespace ba3d {
//------------------------------------------------------------------------------

Geometry::mesh_t Geometry::meshDodecahedron() {
  flt const G  = geometry::goldenRatio,
            G1 = 1/G;

  xyz_vec vs_; vs_.reserve(20);
  for (flt x : {-1, +1})
    for (flt y : {-1, +1})
      for (flt z : {-1, +1})
        vs_.append(xyz(x,y,z));

  for (flt g1 : {-G1, +G1})
    for (flt g : {-G, +G}) {
      vs_.append(xyz(0, g1, g));
      vs_.append(xyz(g1, g, 0));
      vs_.append(xyz(g, 0, g1));
    }

  ENSURE(20 == vs_.count())

  // scale to circumscribed sphere
  flt const F = .5f / vs_.at(0).length();
  for (auto& v : vs_)
    v = v*F;

  //face down
  auto q = QQuaternion::rotationTo(-xyz::_z,
    cross(vs_.at(8)-vs_.at(0), vs_.at(10)-vs_.at(0)));
  for_i (20)
    vs_[i] = q.rotatedVector(vs_.at(i));

  xyz_vec vs; vs.reserve(180);

  auto add5 = [&](idx i1, idx i2, idx i3, idx i4, idx i5) {
    vs.addFan(vs_, {i1, i2, i3, i4, i5, i1});
  };

  add5( 1, 11, 17,  3, 16); // bottom
  add5( 1, 16, 10,  0, 9 );
  add5(16,  3, 12,  2, 10);
  add5( 3, 17,  7, 18, 12);
  add5(17, 11,  5, 19,  7);
  add5(11,  1,  9, 15,  5);

  add5( 8,  4, 15,  9,  0);
  add5(14,  8,  0, 10,  2);
  add5( 6, 14,  2, 12, 18);
  add5(13,  6, 18,  7, 19);
  add5( 4, 13, 19,  5, 15);
  add5( 4,  8, 14,  6, 13);  // top

  ENSURE(180 == vs.count())

  return makeMesh(vs);
}

//------------------------------------------------------------------------------
}
// eof

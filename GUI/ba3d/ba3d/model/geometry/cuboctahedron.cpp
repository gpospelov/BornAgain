// GPL3; https://github.com/jburle/ba3d

#include "../geometry.h"
#include <qmath.h>

namespace ba3d {
//------------------------------------------------------------------------------

Geometry::mesh_t Geometry::meshCuboctahedron(flt rH, flt alpha) { // t/D
  EXPECT(alpha >= flt(M_PI_2))
  EXPECT(rH >= 0)

  flt const D = .5f, H = 2*D / (rH + 1), t = tanf(alpha - flt(M_PI_2));
  flt const Db = D - t*H, Dt = D - t*(2*D - H);

  xyz_vec vs_; vs_.reserve(12);
  flt z[] = {-D, H-D, +D}, d[] = {Db, D, Dt};
  for_i (3)
    for (int x : {-1, +1})
      for (int y : {-1, +1}) {
        flt di = d[i];
        vs_.append(xyz(x*di, y*di, z[i]));
      }

  ENSURE(12 == vs_.count())

  xyz_vec vs; vs.reserve(60);

  vs.addQuad(vs_, 0,  1,  3, 2);
  vs.addQuad(vs_, 8, 10, 11, 9);
  vs.addQuad(vs_, 0,  4,  5, 1);
  vs.addQuad(vs_, 1,  5,  7, 3);
  vs.addQuad(vs_, 3,  7,  6, 2);
  vs.addQuad(vs_, 2,  6,  4, 0);
  vs.addQuad(vs_, 4,  8,  9, 5);
  vs.addQuad(vs_, 5,  9, 11, 7);
  vs.addQuad(vs_, 7, 11, 10, 6);
  vs.addQuad(vs_, 6, 10,  8, 4);

  ENSURE(60 == vs.count())

  return makeMesh(vs);
}

//------------------------------------------------------------------------------
}
// eof

// GPL3; https://github.com/jburle/ba3d

#include "../geometry.h"

namespace ba3d {
//------------------------------------------------------------------------------

Geometry::mesh_t Geometry::meshBox() {
  flt const D = .5f;

  xyz_vec vs_; vs_.reserve(8);
  for (flt x : {-D, +D})
    for (flt y : {-D, +D})
      for (flt z : {-D, +D})
        vs_.append(xyz(x,y,z));

  ENSURE(8 == vs_.count())

  xyz_vec vs; vs.reserve(36);

  vs.addQuad(vs_, 0, 2, 6, 4);
  vs.addQuad(vs_, 1, 5, 7, 3);
  vs.addQuad(vs_, 0, 1, 3, 2);
  vs.addQuad(vs_, 4, 6, 7, 5);
  vs.addQuad(vs_, 0, 4, 5, 1);
  vs.addQuad(vs_, 2, 3, 7, 6);

  ENSURE(36 == vs.count())

  return makeMesh(vs);
}

//------------------------------------------------------------------------------
}
// eof

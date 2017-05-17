// GPL3; https://github.com/jburle/ba3d

#include "../geometry.h"

namespace ba3d {
//------------------------------------------------------------------------------

Geometry::mesh_t Geometry::meshPlane() {
  flt const D = .5f;

  xyz_vec vs; vs.reserve(4);
  vs.addQuad({+D,+D, 0}, {-D,+D, 0}, {-D,-D, 0}, {+D,-D, 0});

  ENSURE(4 == vs.count())

  return makeMesh(vs);
}

//------------------------------------------------------------------------------
}
// eof

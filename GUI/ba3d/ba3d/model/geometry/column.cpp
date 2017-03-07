// GPL3; https://github.com/jburle/ba3d

#include "../geometry.h"
#include <qmath.h>

namespace ba3d {
//------------------------------------------------------------------------------

Geometry::mesh_t Geometry::meshColumn(flt alpha, flt numSides) {
  int  const sides  = qRound(numSides);
  bool const smooth = (0 == sides); // sides: 0->smooth
  int  const slices = smooth ? SLICES : sides;

  flt const R = .5f, Rb = R, Rt = Rb - 2*R/tanf(alpha);

  // mesh of vertices and normals
  xyz_vec vb(slices), vt(slices), nbt(slices);
  flt const nz = (1 - Rt/Rb)*2*R;
  for_int (s, slices) {
    flt th = flt(2*M_PI*s/slices), st = sinf(th), ct = cosf(th);
    xyz vb_(Rb*ct, Rb*st, -R), vt_(Rt*ct, Rt*st, +R);
    vb[s] = vb_; vt[s] = vt_;
    if (smooth)
      nbt[s] = xyz(vb_.x, vb_.y, nz).normalized();
  }

  // make into triangles
  int const nv = 6*2*slices;
  xyz_vec vs; vs.reserve(nv);
  xyz_vec ns; if (smooth) ns.reserve(nv);

  for_int (s, slices) {
    int s1 = s, s2 = (s+1) % slices;

    vs.addTrig(vb.at(s1), xyz(0,0,-R), vb.at(s2));          // bottom
    if (smooth)
      ns.addVert(-xyz::_z, 3);

    vs.addTrig(xyz(0,0,+R), vt.at(s1), vt.at(s2));          // top
    if (smooth)
      ns.addVert(+xyz::_z, 3);

    vs.addQuad(vb.at(s1), vb.at(s2), vt.at(s2), vt.at(s1)); // side
    if (smooth) {
      auto &n1 = nbt.at(s1), &n2 = nbt.at(s2);
      ns.addQuad(n1, n2, n2, n1);
    }
  }

  ENSURE(vs.count() == nv)
  ENSURE(!smooth || ns.count() == nv)

  return makeMesh(vs, smooth ? &ns : nullptr);
}

//------------------------------------------------------------------------------
}
// eof

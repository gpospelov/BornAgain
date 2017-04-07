// GPL3; https://github.com/jburle/ba3d

#include "../geometry.h"
#include <qmath.h>

namespace ba3d {
//------------------------------------------------------------------------------

// cut: 0..1 - how much is cut off off the bottom
Geometry::mesh_t Geometry::meshSphere(flt cut) {
  if (1 <= cut)
    return mesh_t();
  cut = qMax(0.f, cut);
  ENSURE(0 <= cut && cut < 1)

  // 'rings' is 1 less than actual rings (due to poles)
  int rings, slices = SLICES;
  flt minPh, phRge;

  if (cut > 0) {
    minPh = asinf(2*cut - 1);
    phRge = flt(M_PI_2) - minPh;
    rings = qMax(1, qCeil(qreal(RINGS * phRge) / M_PI));
  } else {
    rings = RINGS - 1;
    minPh = flt(M_PI) / rings - flt(M_PI_2);
    phRge = flt(M_PI_2) - minPh;
  }

  ENSURE(qAbs(minPh) < flt(M_PI_2))
  ENSURE(1 <= rings && 2 <= slices)

  // meshes of vertices and normals, without poles, _[ring][slice]
  QVector<xyz_vec> vs_(rings), ns_(rings);
  for (auto& ring: vs_)
    ring.resize(slices);
  for (auto& ring: ns_)
    ring.resize(slices);

  flt const R = .5f;

  for_int (r, rings) {
    flt ph = minPh + phRge * r/rings;
    flt cp = cosf(ph), sp = sinf(ph);

    for_int (s, slices) {
      flt th = flt(2*M_PI*s/slices);
      xyz v(R*cp*cosf(th), R*cp*sinf(th), R*sp);
      vs_[r][s] = v;
      ns_[r][s] = v.normalized();
    }
  }

  // make into triangles
  int const nv = 6*(rings)*slices;
  xyz_vec vs; vs.reserve(nv);
  xyz_vec ns; ns.reserve(nv);

  for_int (r, rings) {
    auto &vr = vs_.at(r), &nr = ns_.at(r);

    for_int (s, slices) {
      int s0 = s, s1 = (s+1) % slices;

      auto &v0 = vr.at(s0), &v1 = vr.at(s1);
      auto &n0 = nr.at(s0), &n1 = nr.at(s1);

      if (r == 0) { // south pole
        xyz vp, n0, n1, np(-xyz::_z);
        if (cut > 0) {
          vp = xyz(0, 0, v0.z);
          n0 = n1 = np;
        } else {
          vp = xyz(0,0,-R);
          n0 = nr.at(s0); n1 = nr.at(s1);
        }
        vs.addTrig(v0, vp, v1);
        ns.addTrig(n0, np, n1);
      }

      if (r+1 == rings) {  // north pole
        xyz vp(0, 0, +R), np(xyz::_z);
        vs.addTrig(v0, v1, vp);
        ns.addTrig(n0, n1, np);
      } else if (1 < rings) { // in between poles
        auto &vr1 = vs_.at(r+1), &nr1 = ns_.at(r+1);
        auto &n2 = nr1.at(s1), &n3 = nr1.at(s0);
        vs.addQuad(v0, v1, vr1.at(s1), vr1.at(s0));
        ns.addQuad(n0, n1, n2, n3);
      }
    }
  }

  return makeMesh(vs, ns);
}

//------------------------------------------------------------------------------
}
// eof

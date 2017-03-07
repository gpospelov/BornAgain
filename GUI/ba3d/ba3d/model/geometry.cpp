// GPL3; https://github.com/jburle/ba3d

#include "geometry.h"
#include "model.h"

namespace ba3d {
//------------------------------------------------------------------------------

Geometry::vn_t::vn_t(xyz::rc v_, xyz::rc n_) : v(v_), n(n_) {}

void Geometry::xyz_vec::addVert(xyz::rc v, int n) {
  for_i (n)
    append(v);
}

void Geometry::xyz_vec::addTrig(xyz::rc v1, xyz::rc v2, xyz::rc v3) {
  append(v1); append(v2); append(v3);
}

void Geometry::xyz_vec::addQuad(xyz::rc v1, xyz::rc v2, xyz::rc v3, xyz::rc v4) {
  addTrig(v1, v2, v3);
  addTrig(v3, v4, v1);
}

void Geometry::xyz_vec::addQuad(Geometry::xyz_vec::rc vs,
                                idx i1, idx i2, idx i3, idx i4) {
  addQuad(vs.at(i1), vs.at(i2), vs.at(i3), vs.at(i4));
}

void Geometry::xyz_vec::addStrip(xyz_vec::rc vs, idx_vec::rc is) {
  EXPECT(is.count() >= 3) // at least one triangle
  for_i (is.count() - 2)
    if (i%2)
      addTrig(vs.at(is.at(i)), vs.at(is.at(1+i)), vs.at(is.at(2+i)));
    else
      addTrig(vs.at(is.at(i)), vs.at(is.at(2+i)), vs.at(is.at(1+i)));
}

void Geometry::xyz_vec::addFan(xyz_vec::rc vs, idx_vec::rc is) {
  EXPECT(is.count() >= 3) // at least one triangle
  auto &ctr = vs.at(is.at(0));
  for_i (is.count() - 2)
    addTrig(ctr, vs.at(is.at(1+i)),
                 vs.at(is.at(2+i)));
}

//------------------------------------------------------------------------------

Geometry::Geometry(geometry::key key_) : key(key_) {
  using namespace geometry;

  switch (key.id) {
  case eid::Plane:
    mesh = meshPlane();
    break;
  case eid::Box:
    mesh = meshBox();
    break;
  case eid::Sphere:
    mesh = meshSphere(key.p1);
    break;
  case eid::Column:
    mesh = meshColumn(key.p1, key.p2);
    break;
  case eid::Icosahedron:
    mesh = meshIcosahedron();
    break;
  case eid::Dodecahedron:
    mesh = meshDodecahedron();
    break;
  case eid::TruncatedBox:
    mesh = meshTruncBox(key.p1);
    break;
  case eid::Cuboctahedron:
    mesh = meshCuboctahedron(key.p1, key.p2);
    break;
  }
}

Geometry::~Geometry() {
  // remove self from the store
  geometryStore().geometryDeleted(*this);
}

Geometry::mesh_t Geometry::makeMesh(xyz_vec::rc vs, xyz_vec const* ns) {
  int nv = vs.count();
  EXPECT(0 == nv%3)
  EXPECT(!ns || nv == ns->count()) // if normals not given, will be computed

  mesh_t mesh(nv);

  for (int i=0 ; i<nv; i+=3) {
    xyz::rc v0 = vs.at(0+i), v1 = vs.at(1+i), v2 = vs.at(2+i);
    xyz const *n0, *n1, *n2; xyz nm;

    if (ns) {
      n0 = &ns->at(0+i); n1 = &ns->at(1+i); n2 = &ns->at(2+i);
    } else {
      nm = cross((v1 - v0), (v2 - v0));
      n0 = n1 = n2 = &nm;
    }

    mesh.append(vn_t(v0,*n0));
    mesh.append(vn_t(v1,*n1));
    mesh.append(vn_t(v2,*n2));
  }

  return mesh;
}

Geometry::mesh_t Geometry::makeMesh(xyz_vec::rc vs, xyz_vec::rc ns) {
  return makeMesh(vs, &ns);
}

//------------------------------------------------------------------------------

shGeo GeometryStore::getGeometry(geometry::key key) {
  auto it = geometries.find(key);
  if (geometries.end() != it) {
    shGeo g = it->toStrongRef();
    if (g)
      return g;
    geometries.erase(it); // it really should not come to this
  }

  shGeo g = shGeo(new Geometry(key));
  geometries.insert(key, g.toWeakRef());
  return g;
}

void GeometryStore::geometryDeleted(Geometry const& g) {
  emit deletingGeometry(&g);
  geometries.remove(g.key);
}

GeometryStore& geometryStore() {
  static GeometryStore gs;
  return gs;
}

//------------------------------------------------------------------------------
}
// eof

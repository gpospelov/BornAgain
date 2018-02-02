// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/model/geometry.cpp
//! @brief     Implements Geometry class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "geometry.h"
#include "model.h"

namespace RealSpace {
//------------------------------------------------------------------------------

Geometry::Vert_Normal::Vert_Normal(const Vector3D& v_, const Vector3D& n_) : v(v_), n(n_) {}

void Geometry::Vertices::addVertex(const Vector3D& v, int n) {
  for(int i=0; i<n; ++i)
    append(v);
}

void Geometry::Vertices::addTriangle(const Vector3D& v1, const Vector3D& v2, const Vector3D& v3) {
  append(v1); append(v2); append(v3);
}

void Geometry::Vertices::addQuad(const Vector3D& v1, const Vector3D& v2,
                                 const Vector3D& v3, const Vector3D& v4) {
  addTriangle(v1, v2, v3);
  addTriangle(v3, v4, v1);
}

void Geometry::Vertices::addQuad(const Vertices& vs,
                                idx i1, idx i2, idx i3, idx i4) {
  addQuad(vs.at(i1), vs.at(i2), vs.at(i3), vs.at(i4));
}

void Geometry::Vertices::addStrip(const Vertices& vs, const Indices& is) {
  Q_ASSERT(is.count() >= 3); // at least one triangle
  for(int i=0; i<is.count()-2; ++i)
    if (i%2)
      addTriangle(vs.at(is.at(i)), vs.at(is.at(1+i)), vs.at(is.at(2+i)));
    else
      addTriangle(vs.at(is.at(i)), vs.at(is.at(2+i)), vs.at(is.at(1+i)));
}

void Geometry::Vertices::addFan(const Vertices& vs, const Indices& is) {
  Q_ASSERT(is.count() >= 3); // at least one triangle
  auto &ctr = vs.at(is.at(0));
  for(int i=0; i<is.count()-2; ++i)
    addTriangle(ctr, vs.at(is.at(1+i)),
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

Geometry::Mesh Geometry::makeMesh(const Vertices& vs, Vertices const* ns) {
  int nv = vs.count();
  Q_ASSERT(0 == nv%3);
  Q_ASSERT(!ns || nv == ns->count()); // if normals not given, will be computed

  Mesh mesh(nv);

  for (int i=0 ; i<nv; i+=3) {
    const Vector3D& v0 = vs.at(0+i), v1 = vs.at(1+i), v2 = vs.at(2+i);
    Vector3D const *n0, *n1, *n2; Vector3D nm;

    if (ns) {
      n0 = &ns->at(0+i); n1 = &ns->at(1+i); n2 = &ns->at(2+i);
    } else {
      nm = cross((v1 - v0), (v2 - v0));
      n0 = n1 = n2 = &nm;
    }

    mesh.append(Vert_Normal(v0,*n0));
    mesh.append(Vert_Normal(v1,*n1));
    mesh.append(Vert_Normal(v2,*n2));
  }

  return mesh;
}

Geometry::Mesh Geometry::makeMesh(const Vertices& vs, const Vertices& ns) {
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

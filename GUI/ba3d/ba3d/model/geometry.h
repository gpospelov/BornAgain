// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/model/geometry.h
//! @brief     Defines Geometry class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BA3D_GEOMETRY_H
#define BA3D_GEOMETRY_H

#include "../def.h"
#include "geometry_inc.h"
#include <QVector>
#include <unordered_map>

namespace RealSpace {
//------------------------------------------------------------------------------

class Buffer;
class GeometryStore;

class Geometry {
  friend class Buffer;
  friend class GeometryStore;
public:
  // vertex+normal pair
  struct Vert_Normal {
    Vector3D v, n;
    Vert_Normal() =default;
    Vert_Normal(const Vector3D& v, const Vector3D& n);
  };

  // vertex indices (for GL)
  typedef quint8 idx;
  using Indices = QVector<idx>;

  // vertices (for GL)
  struct Vertices : QVector<Vector3D>
  {
    using QVector::QVector;

    void addVertex(const Vector3D&, int n = 1); // add a vertex, possibly multiple copies
    void addTriangle(const Vector3D&, const Vector3D&, const Vector3D&); // triangle
    void addQuad(const Vector3D&, const Vector3D&,
                 const Vector3D&, const Vector3D&); // quad as 2 triangles
    void addQuad(const Vertices&, idx, idx, idx, idx);
    void addStrip(const Vertices&, const Indices&); // triangle strip
    void addFan(const Vertices&, const Indices&);   // triangle fan
  };

  // vertex/normal mesh
  using Mesh = QVector<Vert_Normal>;

  Geometry(GeometricID::Key);
  virtual ~Geometry();

private:
  GeometricID::Key m_key;

  Mesh m_mesh;
  // make a mesh from vectors of vertices on (optionally) normals
  static Mesh makeMesh(const Vertices& vs, Vertices const* ns = nullptr);
  static Mesh makeMesh(const Vertices& vs, const Vertices& ns);

  static Mesh meshPlane();
  static Mesh meshBox();
  static Mesh meshSphere(float cut);
  static Mesh meshColumn(float alpha, float sides);
  static Mesh meshIcosahedron();
  static Mesh meshDodecahedron();
  static Mesh meshTruncBox(float tD);
  static Mesh meshCuboctahedron(float rH, float alpha);

  // mesh params for round shapes
  static int const RINGS = 12, SLICES = 24;
};

//------------------------------------------------------------------------------

// a single store keeps existing geometries for sharing
class GeometryStore : public QObject {
  Q_OBJECT
  friend class Geometry;
public:
  shGeo getGeometry(GeometricID::Key);

signals:
  void deletingGeometry(Geometry const*); // signal to canvases

private:
  std::unordered_map<GeometricID::Key, wkGeo, GeometricID::KeyHash> m_geometries;
  void geometryDeleted(Geometry const&);  // ~Geometry() calls this
};

GeometryStore& geometryStore(); // simpleton

//------------------------------------------------------------------------------
}
#endif

// GPL3; https://github.com/jburle/ba3d

#ifndef BA3D_GEOMETRY_H
#define BA3D_GEOMETRY_H

#include "../def.h"
#include "geometry_inc.h"
#include <QVector>

namespace ba3d {
//------------------------------------------------------------------------------

class Buffer;
class GeometryStore;

class Geometry {
  friend class Buffer;
  friend class GeometryStore;
public:
  // vertex+normal pair
  struct vn_t {
    xyz v, n;
    vn_t() = default;
    vn_t(xyz::rc v, xyz::rc n);
  };

  // vertex indices (for GL)
  typedef quint8 idx;
  struct idx_vec : QVector<idx> { typedef QVector<idx> base;
    using base::base;
    typedef idx_vec const& rc;
  };

  // vertices (for GL)
  struct xyz_vec : QVector<xyz> { typedef QVector<xyz> base;
    using base::base;
    typedef xyz_vec const& rc;

    void addVert(xyz::rc, int n = 1); // add a vertex, possibly multiple copies

    void addTrig(xyz::rc, xyz::rc, xyz::rc);          // triangle
    void addQuad(xyz::rc, xyz::rc, xyz::rc, xyz::rc); // quad as 2 triangles
    void addQuad(xyz_vec::rc, idx, idx, idx, idx);
    void addStrip(xyz_vec::rc, idx_vec::rc);          // triangle strip
    void addFan(xyz_vec::rc, idx_vec::rc);            // triangle fan

  };

  // vertex/normal mesh
  typedef QVector<vn_t> mesh_t;

  Geometry(geometry::key);
  virtual ~Geometry();

private:
  geometry::key key;

  mesh_t mesh;
  // make a mesh from vectors of vertices on (optionally) normals
  static mesh_t makeMesh(xyz_vec::rc vs, xyz_vec const* ns = nullptr);
  static mesh_t makeMesh(xyz_vec::rc vs, xyz_vec::rc ns);

  static mesh_t meshPlane();
  static mesh_t meshBox();
  static mesh_t meshSphere(flt cut);
  static mesh_t meshColumn(flt alpha, flt sides);
  static mesh_t meshIcosahedron();
  static mesh_t meshDodecahedron();
  static mesh_t meshTruncBox(flt tD);
  static mesh_t meshCuboctahedron(flt rH, flt alpha);

  // mesh params for round shapes
  static int const RINGS = 12, SLICES = 24;
};

//------------------------------------------------------------------------------

// a single store keeps existing geometries for sharing
class GeometryStore : public QObject {
  Q_OBJECT
  friend class Geometry;
public:
  shGeo getGeometry(geometry::key);

signals:
  void deletingGeometry(Geometry const*); // signal to canvases

private:
  QHash<geometry::key,wkGeo> geometries;
  void geometryDeleted(Geometry const&);  // ~Geometry() calls this
};

GeometryStore& geometryStore(); // simpleton

//------------------------------------------------------------------------------
}
#endif
// eof

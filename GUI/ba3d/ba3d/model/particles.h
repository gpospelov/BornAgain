// GPL3; https://github.com/jburle/ba3d

#ifndef BA3D_PARTICLES_H
#define BA3D_PARTICLES_H

#include "object.h"

namespace ba3d { namespace particle {
//------------------------------------------------------------------------------

enum class kind {
  None,
  FullSphere, FullSpheroid, Cylinder, TruncatedSphere, TruncatedSpheroid,
  Cone, Icosahedron, Dodecahedron, TruncatedCube, Prism6, Cone6, Pyramid,
  Cuboctahedron, Prism3, Tetrahedron, EllipsoidalCylinder, Box,
  HemiEllipsoid, AnisoPyramid,
};

QString const& name(kind);

//------------------------------------------------------------------------------

class Particle : public Object { BASE(Object)
protected:
  Particle(geometry::key);
  xyz turn,   // turn before scale
      scale,  // geometries are of 1-size (box 1x1x1, sphere D=1), need scaling
      offset; // geometries centered around origin; particles stand on z=0 plane

  void set();

public:
  static kind const firstKind = kind::None,
                    lastKind  = kind::AnisoPyramid;

  void transform(xyz rotate, xyz translate);
};

//------------------------------------------------------------------------------
// follow BornAgain manual, chapter 11, Particle form factors

class FullSphere : public Particle {
public:
  FullSphere(flp R);
};

class FullSpheroid : public Particle {
public:
  FullSpheroid(flp R, flp H);
};

class Cylinder : public Particle {
public:
  Cylinder(flp R, flp H);
};

class TruncatedSphere : public Particle {
public:
  TruncatedSphere(flp R, flp H);
};

class TruncatedSpheroid : public Particle {
public:
  TruncatedSpheroid(flp R, flp H, flp fp);
};

class Cone : public Particle {
public:
  Cone(flp R, flp H, flp alpha);
};

class Icosahedron : public Particle {
public:
  Icosahedron(flp L);
};

class Dodecahedron : public Particle {
public:
  Dodecahedron(flp L);
};

class TruncatedCube : public Particle {
public:
  TruncatedCube(flp L, flp t);
};

class Prism6 : public Particle {
public:
  Prism6(flp R, flp H);
};

class Cone6 : public Particle {
public:
  Cone6(flp R, flp H, flp alpha);
};

class Pyramid : public Particle {
public:
  Pyramid(flp L, flp H, flp alpha);
};

class Cuboctahedron : public Particle {
public:
  Cuboctahedron(flp L, flp H, flp rH, flp alpha);
};

class Prism3 : public Particle {
public:
  Prism3(flp L, flp H);
};

class Tetrahedron : public Particle {
public:
  Tetrahedron(flp L, flp H, flp alpha);
};

class EllipsoidalCylinder : public Particle {
public:
  EllipsoidalCylinder(flp Ra, flp Rb, flp H);
};

class Box : public Particle {
public:
  Box(flp L, flp W, flp H);
};

class HemiEllipsoid : public Particle {
public:
  HemiEllipsoid(flp Ra, flp Rb, flp H);
};

class AnisoPyramid : public Particle {
public:
  AnisoPyramid(flp L, flp W, flp H, flp alpha);
};

//------------------------------------------------------------------------------
}}
#endif
// eof

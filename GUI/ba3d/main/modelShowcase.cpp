// GPL3; https://github.com/jburle/ba3d

#include "modelShowcase.h"

//------------------------------------------------------------------------------

using namespace ba3d;

static flt const R = 1;

ModelShowcase::ModelShowcase() : p(nullptr) {

  defEye    = xyz(0, -4*R, 0);
  defCtr    = xyz(0, 0, R);

  Object *o;

  // bounding box
  addBlend(o = new Object(geometry::key(geometry::eid::Box)));
  o->color = QColor(0, 255, 0, 50);
  o->transform(2*R, xyz::_0, xyz(0,0,R));

  // bounding sphere
  addBlend(o = new Object(geometry::key(geometry::eid::Sphere)));
  o->color = QColor(0, 255, 255, 50);
  o->transform(2*R, xyz::_0, xyz(0,0,R));
}

void ModelShowcase::showKind(kind k) {
  delete p;

  if (kind::None == k)
    return;

  add((p = newParticle(k, R)));
}

particle::Particle* ModelShowcase::newParticle(kind k, flp R) {
  using namespace particle;

  flp D = 2*R;

  switch (k) {
  case kind::None:
    return nullptr;
  case kind::FullSphere:
    return new FullSphere(R);
  case kind::FullSpheroid:
    return new FullSpheroid(R/2, D);
  case kind::Cylinder:
    return new Cylinder(R, D);
  case kind::TruncatedSphere:
    return new TruncatedSphere(R, D/3);
  case kind::TruncatedSpheroid:
    return new TruncatedSpheroid(R, 2*R, 1.5);
  case kind::Cone:
    return new Cone(R, D, 1.3f);
  case kind::Icosahedron:
    return new Icosahedron(R * geometry::icosahedronL2R);
  case kind::Dodecahedron:
    return new Dodecahedron(R * geometry::dodecahedronL2R);
  case kind::TruncatedCube:
    return new TruncatedCube(D, D/3);
  case kind::Prism6:
    return new Prism6(R, D);
  case kind::Cone6:
    return new Cone6(R, D, 1.3f);
  case kind::Pyramid:
    return new Pyramid(D, D, 1.3f);
  case kind::Cuboctahedron:
    return new Cuboctahedron(D, R*3/2, 2.f/3, 2);
  case kind::Prism3:
    return new Prism3(R, D);
  case kind::Tetrahedron:
    return new Tetrahedron(R, D, 1.3f);
  case kind::EllipsoidalCylinder:
    return new EllipsoidalCylinder(R, R/2, D);
  case kind::Box:
    return new Box(D, D, D);
  case kind::HemiEllipsoid:
    return new HemiEllipsoid(R, R, D);
  case kind::AnisoPyramid:
    return new AnisoPyramid(R, D, D, 1.3f);
  }
  return nullptr;
}

//------------------------------------------------------------------------------
// eof

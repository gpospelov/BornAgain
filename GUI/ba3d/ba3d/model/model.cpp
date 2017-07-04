// GPL3; https://github.com/jburle/ba3d

#include "model.h"
#include "geometry.h"

namespace ba3d {
//------------------------------------------------------------------------------

Model::Model() : defCamPos(xyz::_1, xyz::_0, xyz::_z) {}

Model::~Model() {
  for (auto o: objects) {
    o->model = nullptr;
    delete o;
  }

  for (auto o: objectsBlend) {
    o->model = nullptr;
    delete o;
  }
}

void Model::clearOpaque() {
  while (!objects.isEmpty())
    delete objects.first();
  emit updated(false);
}

void Model::clearBlend() {
  while (!objectsBlend.isEmpty())
    delete objectsBlend.first();
  emit updated(false);
}

particle::Particle* Model::newParticle(particle::kind k, flp R) {
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

void Model::add(Object* o) {
  EXPECT(o) EXPECT(!o->model)
  o->model = this;
  objects.append(o);
}

void Model::addBlend(Object* o) {
  EXPECT(o) EXPECT(!o->model)
  o->model = this;
  objectsBlend.append(o);
}

void Model::rem(Object* o) {
  int i;
  if ((i = objects.indexOf(o)) >= 0)
    objects.remove(i);
  else if ((i = objectsBlend.indexOf(o)) >= 0)
    objectsBlend.remove(i);
  else
    EXPECT(false); // object not found, should not happen, bad caller!

  o->releaseGeometry();
  o->model = nullptr;
}

void Model::releaseGeometries() {
  for (auto o: objects)
    o->releaseGeometry();
  for (auto o: objectsBlend)
    o->releaseGeometry();
}

void Model::draw(Canvas& canvas) const {
  for (auto o: objects)
    o->draw(canvas);
}

void Model::drawBlend(Canvas& canvas) const {
  for (auto o: objectsBlend)
    o->draw(canvas);
}

//------------------------------------------------------------------------------
}
// eof

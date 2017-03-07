// GPL3; https://github.com/jburle/ba3d

#include "model.h"
#include "geometry.h"

namespace ba3d {
//------------------------------------------------------------------------------

Model::Model() : defEye(xyz::_1), defCtr(xyz::_0), defUp(xyz::_z) {}

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

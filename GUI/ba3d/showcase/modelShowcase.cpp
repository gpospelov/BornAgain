// GPL3; https://github.com/jburle/ba3d

#include "modelShowcase.h"

//------------------------------------------------------------------------------

using namespace ba3d;

static flt const R = 1;

ModelShowcase::ModelShowcase() : p(nullptr) {
  defCamPos.eye = xyz(0, -4*R, 0);
  defCamPos.ctr = xyz(0, 0, R);

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

  emit updated(false);
}

//------------------------------------------------------------------------------
// eof

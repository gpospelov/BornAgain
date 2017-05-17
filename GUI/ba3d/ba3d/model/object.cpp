// GPL3; https://github.com/jburle/ba3d

#include "object.h"
#include "model.h"
#include "geometry.h"
#include "../view/canvas.h"

namespace ba3d {
//------------------------------------------------------------------------------

Object::Object(geometry::key gky_) : color(Qt::gray)
, isNull(false), model(nullptr), gky(gky_) {
}

Object::~Object() {
  releaseGeometry();
  if (model)
    model->rem(this);
}

void Object::transform(flt scale, xyz rotate, xyz translate) {
  transform(xyz(scale,scale,scale), rotate, translate);
}

void Object::transform(xyz scale, xyz rotate, xyz translate) {
  mat.setToIdentity();
  mat.translate(translate);
  mat.rotate(QQuaternion::fromEulerAngles(rotate));
  mat.scale(scale);
}

void Object::transform(xyz turn, xyz scale, xyz rotate, xyz translate) {
  // 1. turn to align with x/y/z as needed
  // 2. scale to desired x/y/z size
  // 3. rotate as needed by the scene
  // 4. move to the position

  mat.setToIdentity();
  mat.translate(translate);
  mat.rotate(QQuaternion::fromEulerAngles(rotate));
  mat.scale(scale);
  mat.rotate(QQuaternion::fromEulerAngles(turn));
}

void Object::releaseGeometry() {
  geo.clear();
}

void Object::draw(Canvas& canvas) {
  if (isNull)
    return;

  if (!geo)
    geo = geometryStore().getGeometry(gky);
  canvas.draw(color, mat, *geo);
}

//------------------------------------------------------------------------------
}
// eof

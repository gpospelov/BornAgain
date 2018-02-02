// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/model/object.cpp
//! @brief     Implements Object class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "object.h"
#include "model.h"
#include "geometry.h"
#include "../view/canvas.h"

namespace RealSpace {
//------------------------------------------------------------------------------

#ifdef Q_OS_LINUX
QColor const clrObject = Qt::lightGray;
#else
QColor const clrObject = Qt::black;
#endif

Object::Object(GeometricID::Key gky_) : color(clrObject)
, isNull(false), model(nullptr), gky(gky_) {
}

Object::~Object() {
  releaseGeometry();
  if (model)
    model->rem(this);
}

void Object::transform(float scale, Vector3D rotate, Vector3D translate) {
  transform(Vector3D(scale,scale,scale), rotate, translate);
}

void Object::transform(Vector3D scale, Vector3D rotate, Vector3D translate) {
  mat.setToIdentity();
  mat.translate(translate);
  mat.rotate(QQuaternion::fromEulerAngles(rotate));
  mat.scale(scale);
}

void Object::transform(Vector3D turn, Vector3D scale, Vector3D rotate, Vector3D translate) {
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
  geo.reset();
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

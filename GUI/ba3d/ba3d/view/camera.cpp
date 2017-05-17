// GPL3; https://github.com/jburle/ba3d

#include "camera.h"
#include <QQuaternion>

namespace ba3d {
//------------------------------------------------------------------------------

Camera::Camera()
: eye(xyz::_z), ctr(), up(xyz::_x), zoom(1)
, vertAngle(60), nearPlane(1), farPlane(10000)
, lightPos(eye), lightPosRotated(lightPos) {
  setAspectRatio(1);
}

void Camera::lookAt(xyz::rc eye_, xyz::rc ctr_, xyz::rc up_) {
  eye = eye_; ctr = ctr_; up = up_; lightPos = eye;
  set();
}

// recalculate dependent params
void Camera::set() {
  matModel.setToIdentity();
  matModel.lookAt((eye-ctr)*zoom + ctr, ctr, up);

  QQuaternion rt(rot * addRot);
  matModel.translate(+ctr);
  matModel.rotate(rt);
  matModel.translate(-ctr);

  lightPosRotated = rt.inverted().rotatedVector(lightPos);
}

void Camera::setAspectRatio(float ratio) {
  matProj.setToIdentity();
  matProj.perspective(vertAngle, ratio, nearPlane, farPlane);
}

void Camera::turnBy(QQuaternion const& rot) {
  addRot = rot;
  set();
}

void Camera::zoomBy(flt zoom_) {
  zoom = zoom_;
  set();
}

void Camera::endTransform(bool keep) {
  if (keep) {
    rot = (rot * addRot).normalized();
    eye = eye * zoom; // TODO limit
  }

  addRot = QQuaternion();
  zoom = 1;

  set();
}

//------------------------------------------------------------------------------
}
// eof

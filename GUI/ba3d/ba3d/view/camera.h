// GPL3; https://github.com/jburle/ba3d

#ifndef BA3D_CAMERA_H
#define BA3D_CAMERA_H

#include "../def.h"
#include <QColor>
#include <QMatrix4x4>

namespace ba3d {
//------------------------------------------------------------------------------

class Canvas;
class Program;

class Camera {
  friend class Canvas;
  friend class Program;
public:
  Camera();

  void lookAt(xyz::rc eye, xyz::rc ctr, xyz::rc up);

private:
  void set();

  void setAspectRatio(float);

  // additional transformation
  void turnBy(QQuaternion const&);
  void zoomBy(flt);
  void endTransform(bool keep);

  // camera setup
  xyz eye, ctr, up;
  flt zoom;
  flt vertAngle, nearPlane, farPlane;

  // light
  xyz lightPos, lightPosRotated;

  // transformation
  QQuaternion rot, addRot;        // rotation, additional rotation
  QMatrix4x4  matModel, matProj;
};

//------------------------------------------------------------------------------
}
#endif
// eof



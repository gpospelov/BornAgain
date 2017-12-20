// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/ba3d/model/camera.h
//! @brief     Defines Camera class
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef BA3D_CAMERA_H
#define BA3D_CAMERA_H

#include "../def.h"
#include <QColor>
#include <QMatrix4x4>
#include <QQuaternion>

namespace ba3d {
//------------------------------------------------------------------------------

class Canvas;
class Program;

class Camera : public QObject {
  Q_OBJECT
  friend class Canvas;
  friend class Program;
public:
  Camera();

  struct pos_t {
    typedef pos_t const& rc;

    pos_t();
    pos_t(xyz::rc eye, xyz::rc ctr, xyz::rc up,
          QQuaternion const& = QQuaternion());

    xyz eye, ctr, up;
    QQuaternion rot;

    pos_t interpolateTo(rc, flt) const;
  };

  void lookAt(pos_t::rc);

  pos_t::rc getPos() const { return pos; }

  void set();

signals:
  void updated(Camera const&);

private:

  void setAspectRatio(float);

  // additional transformation
  void turnBy(QQuaternion const&);
  void zoomBy(flt);
  void endTransform(bool keep);

  // camera setup
  pos_t pos;
  flt zoom;
  flt vertAngle, nearPlane, farPlane;

  // light
  xyz lightPos, lightPosRotated;

  // transformation
  QQuaternion addRot;        // rotation, additional rotation
  QMatrix4x4  matModel, matProj;
};

//------------------------------------------------------------------------------
}
#endif

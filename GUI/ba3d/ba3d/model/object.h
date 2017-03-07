// GPL3; https://github.com/jburle/ba3d

#ifndef BA3D_OBJECT_H
#define BA3D_OBJECT_H

#include "../def.h"
#include "geometry_inc.h"
#include <QColor>
#include <QMatrix4x4>

namespace ba3d {
//------------------------------------------------------------------------------

class Model;
class Canvas;

class Object {
  friend class Model;
public:
  Object(geometry::key);
  virtual ~Object();

  QColor color;

  void transform(flt scale, xyz rotate, xyz translate);
  void transform(xyz scale, xyz rotate, xyz translate);
  void transform(xyz scale, QQuaternion, xyz translate);
  void transform(xyz turn, xyz scale, xyz rotate, xyz translate);

protected:
  bool isNull;

private:
  Model *model;

  geometry::key gky;
  shGeo         geo;      // retrieved on demand
  void releaseGeometry(); // can be released whenever

  QMatrix4x4 mat;
  void draw(Canvas&);
};

//------------------------------------------------------------------------------
}
#endif
// eof

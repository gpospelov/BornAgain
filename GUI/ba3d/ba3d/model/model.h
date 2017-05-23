// GPL3; https://github.com/jburle/ba3d

#ifndef BA3D_MODEL_H
#define BA3D_MODEL_H

#include <ba3d/view/camera.h>
#include "object.h"
#include <QVector>
#include <QHash>

namespace ba3d {
//------------------------------------------------------------------------------

class Canvas;
class Object;

class Model : public QObject {
  Q_OBJECT
  friend class Canvas;
  friend class Camera;
  friend class Object;
public:
  Model();
  virtual ~Model();

  void clear(bool alsoBlend);

  void add(Object*);        // add an opaque object, the model takes ownership
  void addBlend(Object*);   // add a transparent object, the model takes ownership
  void rem(Object*);        // removes an object, the caller becomes responsible

  void releaseGeometries(); // may be called any time

  virtual void cameraUpdated(Camera const&) {}

signals:
  void updated();

protected:
  Camera::pos_t defCamPos;    // default camera params

private:
  QVector<Object*> objects, objectsBlend;

  void draw(Canvas&)      const;
  void drawBlend(Canvas&) const;
};

//------------------------------------------------------------------------------
}
#endif
// eof

// GPL3; https://github.com/jburle/ba3d

#ifndef BA3D_WIDGET_H
#define BA3D_WIDGET_H

#include "def.h"
#include <QWidget>

namespace ba3d {
//------------------------------------------------------------------------------

class Model;
class Canvas;
class Camera;
class Program;

class Widget3D : public QWidget { BASE(QWidget)
  Q_OBJECT
public:
  Widget3D();
 ~Widget3D();

  Camera& cam() { return *camera; }

  void setBackground(QColor const&);
  void setModel(Model*); // model owned elsewhere, may be nullptr
  Model* getModel();

  void update();

private:
  Canvas  *canvas;
  Camera  *camera;
  Program *program;
  QMetaObject::Connection modelUpdated;
};

//------------------------------------------------------------------------------
}
#endif
// eof

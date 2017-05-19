// GPL3; https://github.com/jburle/ba3d

#ifndef BA3D_CANVAS_H
#define BA3D_CANVAS_H

#include "../def.h"
#include <QHash>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

namespace ba3d {
//------------------------------------------------------------------------------

class Camera; class Program; class Model;
class Geometry; class Buffer; class Object;

class Canvas: public QOpenGLWidget, protected QOpenGLFunctions {
  BASE(QOpenGLWidget)
  Q_OBJECT
  friend class Object;
public:
  Canvas();
 ~Canvas();

  void setBgColor(QColor const&);

  // active things, owned elsewhere, may be nullptr
  void setCamera(Camera*);
  void setProgram(Program*);
  void setModel(Model*);
  Model* getModel();

private:
  QRect viewport;
  flt   aspectRatio, colorBgR, colorBgG, colorBgB;

  void setCamera(bool full);

  void initializeGL();
  void resizeGL(int, int);
  void paintGL();

  QVector3D lastV;    // unprojected vector
  flt       lastY;    // screen coordinate
  QMatrix4x4 matModel, matProj;
  QVector3D  unproject(QPoint const&);

  enum {btnNONE, btnTURN, btnZOOM} mouseButton;
  void mousePressEvent(QMouseEvent*);
  void mouseMoveEvent(QMouseEvent*);
  void mouseReleaseEvent(QMouseEvent*);

  Camera  *camera;
  Program *program;
  Model   *model;

  QHash<Geometry const*, Buffer*> buffers;
  void releaseBuffer(Geometry const*);
  void releaseBuffers();

  void draw(QColor const&, QMatrix4x4 const&, Geometry const&);
};

//------------------------------------------------------------------------------
}
#endif
// eof

// GPL3; https://github.com/jburle/ba3d

#ifndef BA3D_PROGRAM_H
#define BA3D_PROGRAM_H

#include "../def.h"
#include <QOpenGLShaderProgram>

namespace ba3d {
//------------------------------------------------------------------------------

class Camera;
class Canvas;

class Program: public QOpenGLShaderProgram { BASE(QOpenGLShaderProgram)
  friend class Canvas;
public:
  Program();

private:
  void needsInit(); // mark as needed init
  void init();      // inits, if needed

  void set(Camera const&);
  void set(QColor const&);      // object color
  void set(QMatrix4x4 const&);  // object transf

  bool doInit;
  int  locMatProj, locMatModel, locMatObject,
       locLightPos, locColor;
};

//------------------------------------------------------------------------------
}
#endif
// eof
